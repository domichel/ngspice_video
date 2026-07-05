This repo demonstrate how to use ngspice to make videos.
========================================================

It is also an example on how to use 2 Foreach loops into a ngspice command file to run successive parametric simulations with different parameters.

The main use cases are two:

1) is to have fun using ngspice to make movies.

2) is to get a practical way to use simulation results when they just gives too many plots.

Making a video allow us to navigate into the results as we want.

To watch 2 example videos made with that simulation, see https://www.youtube.com/watch?v=oyno5S3Gqs4 and the same with inverted colors: https://www.youtube.com/watch?v=44GZ5FE5tSQ

To work and be useful, we use a Simulation.cmd file that run the parametric simulations, change the titles of the plots and show us what parameters was used for each single plot.

It is 2 main files: Clapp_pentode_1.cir is the ngspice net list of a Clapp vacuum tube oscillator. At the end of it, we include Simulation.cmd, a ngspice command file that tell ngespice what to do. Read the comments into that file.

It is a few auxialiary file. EF89.inc contain the valve model used into the simulation. The EF89Ayumi.inc, is another model for that tube. Not tested at that time if it will work but it is a nice model too.

Clapp_pentode_1.sch is the gschem schematic used to generate Clapp_pentode_1.cir. It should work with the Lepton EDA too. Ra is connected between the + supply and the G2 of the EF89. I didn't get the time to change its name, but it doesn't matter for that simulation. In the real circuits I made with that oscillator, the valve is used as a triode with its G2 directly connected with its anode to the + supply. That too doesn't matter for that simulation.

To run the complete simulation (a 250usec transient simulation of that vacuum tube Clapp oscillator at atartup) run

	ngspice Clapp_pentode_1.cir

This will generate 1496 plot files, can take a while and need to be run only 1 time.
The index into Simulation.cmd begin at 1000. The plot title begin at 1. To know which file correspond to a given plot, do <plot_title_number> + 999.
To remove thesse files, you may run

	rm -f *.png

To generate some video from these png files, run

	./makevideos <fps>
where fps is the framerate of the video and must be >=1.

	./makevideos 60
will generate 2 files with the same content, one with the original ngspice colors as defined into Simulation.cmd, the second one with inverted colors.
These are 24 seconds video files.

	./makevideos 1
will do the same identical videos with a length of almost 25 minutes.

	./makevideos 6
may or not be a good compromise between readabilty and video length.

To adjust the ffmpeg options, read its documentation and see https://www.gumlet.com/learn/ffmpeg-images-to-video/

NB: The gschem dirctory is provided as it. It contain a gschem symbol for the EF89 and a few other files.

Copyright Dominique Michel 2026

This software, examples and documentation are licensed under the GPL-3.0 license.
