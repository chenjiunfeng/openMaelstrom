#pragma once
#include <utility/identifier.h>
/*
Module used to iteratively created a stable surface distance for every particle in the simulation. Very slow.
*/
namespace SPH{
	namespace detection{
		struct Memory{
			// basic information
			parameter_u<parameters::num_ptcls> num_ptcls;
			parameter_u<parameters::timestep> timestep;
			parameter_u<parameters::radius> radius;
			parameter_u<parameters::rest_density> rest_density;
			parameter_u<parameters::max_numptcls> max_numptcls;

			write_array_u<arrays::debugArray> debugArray;

			// parameters
			parameter_u<parameters::xsph_viscosity> xsph_viscosity;
			parameter_u<parameters::surface_levelLimit> surface_levelLimit;
			parameter_u<parameters::surface_neighborLimit> surface_neighborLimit;
			parameter_u<parameters::surface_phiMin> surface_phiMin;
			parameter_u<parameters::surface_phiChange> surface_phiChange;
			parameter_u<parameters::surface_distanceFieldDistances> surface_distanceFieldDistances;

			// temporary resources (mapped as read/write)
			write_array_u<arrays::decisionBuffer> decisionBuffer;
			write_array_u<arrays::markerBuffer> markerBuffer;
			write_array_u<arrays::changeBuffer> changeBuffer;
			write_array_u<arrays::particleNormal> particleNormal;

			// input resources (mapped as read only)
			const_array_u<arrays::position> position;
			const_array_u<arrays::density> density;
			const_array_u<arrays::volume> volume;
			const_array_u<arrays::velocity> velocity;

			// output resources (mapped as read/write)
			// swap resources (mapped as read/write)
			swap_array_u<arrays::distanceBuffer> distanceBuffer;
			swap_array_u<arrays::surface_idxBuffer> surface_idxBuffer;

			// cell resources (mapped as read only)
			parameter_u<parameters::grid_size> grid_size;
			parameter_u<parameters::min_domain> min_domain;
			parameter_u<parameters::max_domain> max_domain;
			parameter_u<parameters::cell_size> cell_size;
			parameter_u<parameters::hash_entries> hash_entries;
			parameter_u<parameters::min_coord> min_coord;
			parameter_u<parameters::mlm_schemes> mlm_schemes;

			const_array_u<arrays::cellBegin> cellBegin;
			const_array_u<arrays::cellEnd> cellEnd;
			const_array_u<arrays::cellSpan> cellSpan;
			const_array_u<arrays::hashMap> hashMap;
			const_array_u<arrays::compactHashMap> compactHashMap;
			const_array_u<arrays::compactCellSpan> compactCellSpan;
			const_array_u<arrays::MLMResolution> MLMResolution;

			// neighborhood resources (mapped as read only)
			const_array_u<arrays::neighborList> neighborList;
			const_array_u<arrays::neighborListLength> neighborListLength;
			const_array_u<arrays::spanNeighborList> spanNeighborList;
			const_array_u<arrays::compactCellScale> compactCellScale;
			const_array_u<arrays::compactCellList> compactCellList;
			const_array_u<arrays::neighborMask> neighborMask;

			// virtual resources (mapped as read only)
			parameter_u<parameters::boundaryCounter> boundaryCounter;
			parameter_u<parameters::ptcl_spacing> ptcl_spacing;
			parameter_u<parameters::boundaryLUTSize> boundaryLUTSize;
			parameter_u<parameters::LUTOffset> LUTOffset;

			const_array_u<arrays::boundaryPlanes> boundaryPlanes;
			const_array_u<arrays::boundaryPlaneVelocity> boundaryPlaneVelocity;
			const_array_u<arrays::offsetLUT> offsetLUT;
			const_array_u<arrays::splineLUT> splineLUT;
			const_array_u<arrays::spline2LUT> spline2LUT;
			const_array_u<arrays::splineGradientLUT> splineGradientLUT;
			const_array_u<arrays::spikyLUT> spikyLUT;
			const_array_u<arrays::spikyGradientLUT> spikyGradientLUT;
			const_array_u<arrays::cohesionLUT> cohesionLUT;
			const_array_u<arrays::volumeLUT> volumeLUT;
			const_array_u<arrays::adhesionLUT> adhesionLUT;

			// volume boundary resources (mapped as read only)
			parameter_u<parameters::volumeBoundaryCounter> volumeBoundaryCounter;

			const_array_u<arrays::volumeBoundaryVolumes> volumeBoundaryVolumes;
			const_array_u<arrays::volumeBoundaryDimensions> volumeBoundaryDimensions;
			const_array_u<arrays::volumeBoundaryMin> volumeBoundaryMin;
			const_array_u<arrays::volumeBoundaryMax> volumeBoundaryMax;
			const_array_u<arrays::volumeBoundaryDensity> volumeBoundaryDensity;
			const_array_u<arrays::volumeBoundaryVolume> volumeBoundaryVolume;
			const_array_u<arrays::volumeBoundaryVelocity> volumeBoundaryVelocity;
			const_array_u<arrays::volumeBoundaryAngularVelocity> volumeBoundaryAngularVelocity;
			const_array_u<arrays::volumeBoundaryPosition> volumeBoundaryPosition;
			const_array_u<arrays::volumeBoundaryQuaternion> volumeBoundaryQuaternion;
			const_array_u<arrays::volumeBoundaryTransformMatrix> volumeBoundaryTransformMatrix;
			const_array_u<arrays::volumeBoundaryTransformMatrixInverse> volumeBoundaryTransformMatrixInverse;
			const_array_u<arrays::volumeBoundaryKind> volumeBoundaryKind;
			const_array_u<arrays::volumeBoundaryInertiaMatrix> volumeBoundaryInertiaMatrix;
			const_array_u<arrays::volumeBoundaryInertiaMatrixInverse> volumeBoundaryInertiaMatrixInverse;

			
			using swap_arrays = std::tuple<arrays::distanceBuffer, arrays::surface_idxBuffer>;
			using input_arrays = std::tuple<arrays::position, arrays::density, arrays::volume, arrays::velocity>;
			using output_arrays = std::tuple<>;
			using temporary_arrays = std::tuple<arrays::decisionBuffer, arrays::markerBuffer, arrays::changeBuffer, arrays::particleNormal>;
			using basic_info_params = std::tuple<parameters::num_ptcls, parameters::timestep, parameters::radius, parameters::rest_density, parameters::max_numptcls>;
			using cell_info_params = std::tuple<parameters::grid_size, parameters::min_domain, parameters::max_domain, parameters::cell_size, parameters::hash_entries, parameters::min_coord, parameters::mlm_schemes>;
			using cell_info_arrays = std::tuple<arrays::cellBegin, arrays::cellEnd, arrays::cellSpan, arrays::hashMap, arrays::compactHashMap, arrays::compactCellSpan, arrays::MLMResolution>;
			using virtual_info_params = std::tuple<parameters::boundaryCounter, parameters::ptcl_spacing, parameters::boundaryLUTSize, parameters::LUTOffset>;
			using virtual_info_arrays = std::tuple<arrays::boundaryPlanes, arrays::boundaryPlaneVelocity, arrays::offsetLUT, arrays::splineLUT, arrays::spline2LUT, arrays::splineGradientLUT, arrays::spikyLUT, arrays::spikyGradientLUT, arrays::cohesionLUT, arrays::volumeLUT, arrays::adhesionLUT>;
			using boundaryInfo_params = std::tuple<parameters::volumeBoundaryCounter>;
			using boundaryInfo_arrays = std::tuple<arrays::volumeBoundaryVolumes, arrays::volumeBoundaryDimensions, arrays::volumeBoundaryMin, arrays::volumeBoundaryMax, arrays::volumeBoundaryDensity, arrays::volumeBoundaryVolume, arrays::volumeBoundaryVelocity, arrays::volumeBoundaryAngularVelocity, arrays::volumeBoundaryPosition, arrays::volumeBoundaryQuaternion, arrays::volumeBoundaryTransformMatrix, arrays::volumeBoundaryTransformMatrixInverse, arrays::volumeBoundaryKind, arrays::volumeBoundaryInertiaMatrix, arrays::volumeBoundaryInertiaMatrixInverse>;
			using neighbor_info_arrays = std::tuple<arrays::neighborList, arrays::neighborListLength, arrays::spanNeighborList, arrays::compactCellScale, arrays::compactCellList, arrays::neighborMask>;
			using parameters = std::tuple<parameters::xsph_viscosity, parameters::surface_levelLimit, parameters::surface_neighborLimit, parameters::surface_phiMin, parameters::surface_phiChange, parameters::surface_distanceFieldDistances>;
			constexpr static const bool resort = false;
constexpr static const bool inlet = false;
		};
		//valid checking function
		inline bool valid(Memory){
			bool condition = false;
			condition = condition || get<parameters::modules::surfaceDetection>() == true;
			return condition;
		}
		
		void distance(Memory mem = Memory());
	} // namspace detection
}// namespace SPH
