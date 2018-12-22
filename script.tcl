############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project Reconfigurable
set_top stream
add_files Reconfigurable/solution1/app_config.hpp
add_files Reconfigurable/solution1/buffer.cpp
add_files Reconfigurable/solution1/buffer.hpp
add_files Reconfigurable/solution1/frame.cpp
add_files Reconfigurable/solution1/frame.hpp
add_files Reconfigurable/hamming.hpp
add_files Reconfigurable/solution1/main.cpp
add_files Reconfigurable/solution1/phase_correlation.cpp
add_files Reconfigurable/solution1/phase_correlation.hpp
add_files -tb Reconfigurable/solution1/app_config.hpp
add_files -tb Reconfigurable/solution1/streamulator.cpp
open_solution "solution1"
set_part {xc7z020clg400-1} -tool vivado
create_clock -period 10 -name default
source "./Reconfigurable/solution1/directives.tcl"
csim_design -ldflags {-g} -clean
csynth_design
cosim_design -ldflags {-g}
export_design -rtl verilog -format ip_catalog
