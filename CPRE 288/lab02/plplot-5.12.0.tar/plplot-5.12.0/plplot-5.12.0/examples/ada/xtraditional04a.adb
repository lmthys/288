--	Log plot demo.

-- Copyright (C) 2007 - 2011 Jerry Bauck

-- This file is part of PLplot.

-- PLplot is free software; you can redistribute it and/or modify
-- it under the terms of the GNU Library General Public License as published
-- by the Free Software Foundation; either version 2 of the License, or
-- (at your option) any later version.

-- PLplot is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU Library General Public License for more details.

-- You should have received a copy of the GNU Library General Public License
-- along with PLplot; if not, write to the Free Software
-- Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

with
    System,
    Ada.Strings.Unbounded,
    Ada.Numerics,
    Ada.Numerics.Long_Elementary_Functions,
    PLplot_Auxiliary,
    PLplot_Traditional;
use
    System,
    Ada.Strings.Unbounded,
    Ada.Numerics,
    Ada.Numerics.Long_Elementary_Functions,
    PLplot_Auxiliary,
    PLplot_Traditional;

procedure xtraditional04a is

    procedure plot1(Plot_Type : Integer) is
        freql, ampl, phase : Real_Vector(0 .. 100);
        f0, freq : Long_Float;
    begin
        pladv(0);
        f0 := 1.0;
        for i in freql'range loop
            freql(i) := -2.0 + Long_Float(i) / 20.0;
            freq := 10.0 ** freql(i);
            ampl(i) := 20.0 * log(1.0 / sqrt(1.0 + (freq / f0) ** 2.0), 10.0);
            phase(i) := -(180.0 / pi) * arctan(freq / f0);
        end loop;

        plvpor(0.15, 0.85, 0.1, 0.9);
        plwind(-2.0, 3.0, -80.0, 0.0);

        -- Try different axis and labelling styles.
        plcol0(1);

        if Plot_Type = 0 then
            plbox("bclnst", 0.0, 0, "bnstv", 0.0, 0);
        elsif Plot_Type = 1 then
            plbox("bcfghlnst", 0.0, 0, "bcghnstv", 0.0, 0);
        end if;

        -- Plot ampl vs freq
        plcol0(2);
        plline(freql, ampl);
        plcol0(2);
        plptex(1.6, -30.0, 1.0, -20.0, 0.5, "-20 dB/decade");

        -- Put labels on
        plcol0(1);
        plmtex("b", 3.2, 0.5, 0.5, "Frequency");
        plmtex("t", 2.0, 0.5, 0.5, "Single Pole Low-Pass Filter");
        plcol0(2);
        plmtex("l", 5.0, 0.5, 0.5, "Amplitude (dB)");

        -- For the gridless case, put phase vs freq on same plot
        if Plot_Type = 0 then
            plcol0(1);
            plwind(-2.0, 3.0, -100.0, 0.0);
            plbox("", 0.0, 0, "cmstv", 30.0, 3);
            plcol0(3);
            plline(freql, phase);
            plstring(freql, phase, "#(728)");
            plcol0(3);
            plmtex("r", 5.0, 0.5, 0.5, "Phase shift (degrees)");
        end if;

        plscol0a(15, 32, 32, 32, 0.70);

        -- Draw the legends.
        if Plot_Type = 0 then -- Make a legend with two entries.
            declare
                text, symbols : Legend_String_Array_Type(0 .. 1);
                opt_array : Integer_Array_1D(0 .. 1);
                text_colors, line_colors, line_styles: Integer_Array_1D(0..1);
                symbol_numbers, symbol_colors : Integer_Array_1D(0 .. 1);
                line_widths, symbol_scales : Real_Vector(0 .. 1);
                legend_width, legend_height  : Long_Float;
                -- Dummy arrays for unused entities. C uses null arguments but we can't.
                Box_Colors, Box_Patterns : Integer_Array_1D(0 .. 1):= (others => 0);
                Box_Scales, Box_Line_Widths : Real_Vector(0 .. 1):= (others => 1.0);
            begin
                -- First legend entry.
                opt_array(0)   := Legend_Line;
                text_colors(0) := 2;
                text(0)        := To_Unbounded_String("Amplitude");
                line_colors(0) := 2;
                line_styles(0) := 1;
                line_widths(0) := 1.0;
                symbol_colors(0)  := 3;   -- Don't care; not used.
                symbol_scales(0)  := 1.0; -- Don't care; not used.
                symbol_numbers(0) := 4;   -- Don't care; not used.
                symbols(0) := To_Unbounded_String("#(728)"); -- Don't care; not used.

                -- Second legend entry.
                opt_array(1)      := Legend_Line + Legend_Symbol;
                text_colors(1)    := 3;
                text(1)           := To_Unbounded_String("Phase shift");
                line_colors(1)    := 3;
                line_styles(1)    := 1;
                line_widths(1)    := 1.0;
                symbol_colors(1)  := 3;
                symbol_scales(1)  := 1.0;
                symbol_numbers(1) := 4;
                symbols(1)        := To_Unbounded_String("#(728)");

                pllegend(legend_width, legend_height,
                    Legend_Background + Legend_Bounding_Box, 0,
                    0.0, 0.0, 0.1, 15,
                    1, 1, 0, 0,
                    opt_array,
                    1.0, 1.0, 2.0,
                    1.0, text_colors, text,
                    Box_Colors, Box_Patterns,
                    Box_Scales, Box_Line_Widths,
                    line_colors, line_styles, line_widths,
                    symbol_colors, symbol_scales, symbol_numbers, symbols);
            end; -- declare block

        elsif Plot_Type = 1 then -- Make a legend with one entry.
            declare
                text, symbols : Legend_String_Array_Type(0 .. 0);
                opt_array : Integer_Array_1D(0 .. 0);
                text_colors, line_colors, line_styles : Integer_Array_1D(0..0);
                symbol_numbers, symbol_colors : Integer_Array_1D(0 .. 0);
                line_widths, symbol_scales : Real_Vector(0 .. 0);
                legend_width, legend_height  : Long_Float;
                -- Dummy arrays for unused entities. C uses null arguments but we can't.
                Box_Colors, Box_Patterns : Integer_Array_1D(0 .. 0);
                Box_Scales, Box_Line_Widths : Real_Vector(0 .. 0);
            begin
                -- First legend entry.
                opt_array(0)   := Legend_Line;
                text_colors(0) := 2;
                text(0)        := To_Unbounded_String("Amplitude");
                line_colors(0) := 2; -- fixme Use declared constants, not integers.
                line_styles(0) := 1;
                line_widths(0) := 1.0;
                symbol_colors(0)  := 3;   -- Don't care; not used.
                symbol_scales(0)  := 1.0; -- Don't care; not used.
                symbol_numbers(0) := 4;   -- Don't care; not used.
                symbols(0) := To_Unbounded_String("#(728)"); -- Don't care; not used.
                Box_Colors(0)      := 0;
                Box_Patterns(0)    := 0;
                Box_Line_Widths(0) := 0.0;
                Box_Scales(0)      := 0.0;

                pllegend(legend_width, legend_height,
                    Legend_Background + Legend_Bounding_Box, 0,
                    0.0, 0.0, 0.1, 15, -- fixme Replace colors and styles with names.
                    1, 1, 0, 0,
                    opt_array,
                    1.0, 1.0, 2.0,
                    1.0, text_colors, text,
                    Box_Colors, Box_Patterns,
                    Box_Scales, Box_Line_Widths,
                    line_colors, line_styles, line_widths,
                    symbol_colors, symbol_scales, symbol_numbers, symbols);
            end; -- declare block
        end if;
    end plot1;
begin
    -- Parse and process command line arguments
    plparseopts(PL_PARSE_FULL);

    -- Initialize plplot
    plinit;
    plfont(2);

    -- Make log plots using two different styles.
    plot1(0);
    plot1(1);

    plend;
end xtraditional04a;
