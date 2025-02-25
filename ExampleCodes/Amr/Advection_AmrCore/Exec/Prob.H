#ifndef PROB_H_
#define PROB_H_

#include <AMReX_Box.H>
#include <AMReX_FArrayBox.H>
#include <AMReX_Geometry.H>

#include <AMReX_Gpu.H>        // For AMREX_GPU_HOST_DEVICE macro and related definitions
#include <cmath>
#include <algorithm>

// Helper inline function for squaring a number.
AMREX_GPU_HOST_DEVICE
inline amrex::Real sq(amrex::Real x) { 
    return x * x; 
}

AMREX_GPU_DEVICE
AMREX_FORCE_INLINE
amrex::Real init_zalesak(const amrex::GpuArray<amrex::Real, 3>& xyz,
                         const amrex::GpuArray<amrex::Real, 3>& center,
                         amrex::Real radius,
                         amrex::Real width,
                         amrex::Real height)
{
    // Compute c = radius - ||xyz - center||
    amrex::Real dx = xyz[0] - center[0];
    amrex::Real dy = xyz[1] - center[1];
    amrex::Real dz = xyz[2] - center[2];
    amrex::Real c = radius - std::sqrt(sq(dx) + sq(dy) + sq(dz));

    // Compute b1, b2, h1, and h2.
    amrex::Real b1 = center[0] - 0.5 * width;
    amrex::Real b2 = center[0] + 0.5 * width;
    amrex::Real h1 = center[1] - radius * std::cos(std::asin(0.5 * width / radius));
    amrex::Real h2 = center[1] - radius + height;

    amrex::Real b;
    amrex::Real result;

    // Translate the Fortran conditionals to C++.
    // Note: Fortran arrays are 1-indexed; in C++ they are 0-indexed.
    if (c >= 0.0 && xyz[0] <= b1 && xyz[1] <= h2) {
        b = b1 - xyz[0];
        result = (c < b ? c : b); // std::min equivalent
    }
    else if (c >= 0.0 && xyz[0] >= b2 && xyz[1] <= h2) {
        b = xyz[0] - b2;
        result = (c < b ? c : b);
    }
    else if (c >= 0.0 && xyz[0] >= b1 && xyz[0] <= b2 && xyz[1] >= h2) {
        b = xyz[1] - h2;
        result = (c < b ? c : b);
    }
    else if (c >= 0.0 && xyz[0] <= b1 && xyz[1] >= h2) {
        // Distance from (xyz[0], xyz[1]) to (b1, h2)
        b = std::sqrt(sq(xyz[0] - b1) + sq(xyz[1] - h2));
        result = (c < b ? c : b);
    }
    else if (c >= 0.0 && xyz[0] >= b2 && xyz[1] >= h2) {
        // Distance from (xyz[0], xyz[1]) to (b2, h2)
        b = std::sqrt(sq(xyz[0] - b2) + sq(xyz[1] - h2));
        result = (c < b ? c : b);
    }
    else if (xyz[0] >= b1 && xyz[0] <= b2 && xyz[1] <= h2 && xyz[1] >= h1) {
        // Negative minimum of distances in x from b1 or b2, and in y from h2.
        amrex::Real d1 = std::abs(xyz[0] - b1);
        amrex::Real d2 = std::abs(xyz[0] - b2);
        amrex::Real d3 = std::abs(xyz[1] - h2);
        amrex::Real min_val = (d1 < d2 ? d1 : d2);
        min_val = (min_val < d3 ? min_val : d3);
        result = -min_val;
    }
    else if (xyz[0] >= b1 && xyz[0] <= b2 && xyz[1] <= h1) {
        amrex::Real d1 = std::sqrt(sq(xyz[0] - b1) + sq(xyz[1] - h1));
        amrex::Real d2 = std::sqrt(sq(xyz[0] - b2) + sq(xyz[1] - h1));
        result = -(d1 < d2 ? d1 : d2);
    }
    else {
        result = c;
    }

    return result;
}

// The init_zalesak function for AMReX
AMREX_GPU_DEVICE
AMREX_FORCE_INLINE
void initdata(amrex::Box const& bx, 
			    amrex::Array4<amrex::Real> const& phi, 
				const amrex::GpuArray<amrex::Real, 3>& prob_lo,
				amrex::GpuArray<amrex::Real,AMREX_SPACEDIM> const& dx)
{

	using namespace amrex;

    const auto lo = lbound(bx);
    const auto hi = ubound(bx);

	amrex::GpuArray<amrex::Real, 3> center = {-1e10-0.25, 0.0, 0.0};
	amrex::GpuArray<amrex::Real, 3> xyz;
	amrex::Real radius = 1e10;
	amrex::Real width = 0.0;
	amrex::Real height = 0.0;
	amrex::Real nfine = 50;
	
	 for (int k = lo.z; k <= hi.z; ++k) {
		Real z = prob_lo[2] + (0.5+k) * dx[2];
        for (int j = lo.y; j <= hi.y; ++j) {
            Real y = prob_lo[1] + (0.5+j) * dx[1];
            for (int i = lo.x; i <= hi.x; ++i) {
                Real x = prob_lo[0] + (0.5+i) * dx[0];	
				for(int jj = 0; jj<nfine;jj++){
					for(int ii = 0; ii<nfine;ii++){
						xyz[0] = x + (ii+0.5)*dx[0]/nfine; 
						xyz[1] = y + (jj+0.5)*dx[1]/nfine;
						xyz[2] = 0.0;
						amrex::Real tmp = init_zalesak(xyz,center,radius,width,height);
						if(tmp > 0.0){
							phi(i,j,k) = phi(i,j,k) + 1.0/(nfine*nfine);
						}
					}
				}	
			}
		}
	}			
}




#endif
