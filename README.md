This repo demonstrate how to use ngspice to make videos.
========================================================

It is also a good example on how to use 2 Foreach loops into a ngspice command file.

The main use cases are two:

1) is to have fun using ngspice to make movies.

2) is to get a practical way to use simulation results when they just gives too many plots.

Making a video allow us to navigate into the results as we want.

To work and be useful, we use a Simulation.cmd file that run the parametric simulations, change the titles of the plots and show us what parameters was used for each single plot.

To run the complete simulation (a 250usec transient simulation of a vacuum tube Clapp oscillator at atartup) run

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

NB: The gschem dirctory is provided as it. It contain a gschem symbol for the EF89 and a few other files.

Copyright Dominique Michel 2026

This software, examples and documentation are licensed under the GPL v. 1.3 or later.
