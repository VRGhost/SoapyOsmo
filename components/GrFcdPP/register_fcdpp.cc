/*
 * Copyright 2014 Free Software Foundation, Inc.
 *
 * This file is part of GrOsmoSDR support modules
 *
 * GrOsmoSDR is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GrOsmoSDR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GrOsmoSDR; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 *
 *
 * Author: Ilja Orlovs
 */

#include <SoapySDR/Registry.hpp>
#include "GrOsmoSDRInterface.hpp"
#include "arg_helpers.h"
 
#include "fcd_source_c.h"

#include <cstdlib>

static std::vector<SoapySDR::Kwargs> find__GNURADIO_FCDPP(const SoapySDR::Kwargs &args)
{
    std::vector<SoapySDR::Kwargs> results;

    //call the get_devices() on the source or sink, but not both
    // #if 1
    std::vector<std::string> source_results = GNURADIO_FCDPP_source_c::get_devices();
    for (size_t i = 0; i < source_results.size(); i++)
    {
        results.push_back(params_to_dict(source_results[i]));
    }
    // #elif 0
    // std::vector<std::string> sink_results = GNURADIO_FCDPP_sink_c::get_devices();
    // for (size_t i = 0; i < sink_results.size(); i++)
    // {
    //     results.push_back(params_to_dict(sink_results[i]));
    // }
    // #endif

    //no device number specified, return all results
    if (args.count("GNURADIO_FCDPP") == 0) return results;

    //device number is used as a filter when specified
    std::vector<SoapySDR::Kwargs> filteredResults;
    const int devNum = atoi(args.at("GNURADIO_FCDPP").c_str());
    for (size_t i = 0; i < results.size(); i++)
    {
        if (
            results[i].count("GNURADIO_FCDPP") == 0 or //driver doesn't support filter
            devNum == atoi(results[i].at("GNURADIO_FCDPP").c_str()) //or device match
        )
        {
            filteredResults.push_back(results[i]);
        }
    }

    return filteredResults;
}

static SoapySDR::Device *make__GNURADIO_FCDPP(const SoapySDR::Kwargs &args)
{
    //convert args to param string
    std::string params;
    for (SoapySDR::Kwargs::const_iterator it = args.begin(); it != args.end(); ++it)
    {
        if (not params.empty()) params += ",";
        params += it->first + "=" + it->second;
    }

    //new device
    GrOsmoSDRInterface *device = new GrOsmoSDRInterface("GNURADIO_FCDPP");

    //call factories when they exist
    #if 0
    device->installSource(make_GNURADIO_FCDPP_source_c(params));
    #endif
    #if 0
    device->installSink(make_GNURADIO_FCDPP_sink_c(params));
    #endif

    //done
    return device;
}

static SoapySDR::Registry register__GNURADIO_FCDPP("GNURADIO_FCDPP", &find__GNURADIO_FCDPP, &make__GNURADIO_FCDPP, SOAPY_SDR_ABI_VERSION);
