* Make a video with ngspice
* Need ngspice and imagemagick
* ngspice will do many simulations -- that will take a while,
* save the resulting curves into ps files, convert them to png files
* and delete the ps files.
* It generate an index file of the png files -- Maybe someone will use it.

* The helper bash script 'makevideos' can then be used to generate the videos.
* It need ffmpeg.

* See READNE.md for details.

.INCLUDE pspice.alias

.control
*.options method = gear

set val_ra = 10k
*let start_ra = 10k
*let stop_ra = 330k
*let step_c1 = 1n
let val_cl = 1000m

let filenb = 1000
let step_a = 1
set fnb = $&filenb

set hcopydevtype=postscript
set hcopypscolor=1
*set color0=rgb:F/F/F $ background
*set color1=rgb:0/0/0 $ grid and text
*set color2=rgb:F/0/0
*set color3=rgb:F/3/3
*set color4=rgb:F/6/6
*set color5=rgb:F/9/9
*set color6=rgb:0/F/0
*set color7=rgb:3/F/3
*set color8=rgb:6/F/6
*set color9=rgb:9/F/9

* create mplayer input file: TODO: resume aborted run
echo -n "" > index.txt
* loop 1 - choose one
* foreach val_ra 10k 33k 100k 330k
foreach val_cl 1000m 500m 220m 163m 100m 50m 16.3m 10m 5m 1.63m 1m 500u 163u 100u 50u 16.3u 10u
    alter Ra $val_ra
    alter Cl $val_cl

	* boucle2
	foreach val_c2 22p 27p 33p 39p 47p 56p 68p 82p 100p 120p 150p 180p 220p 270p 330p 390p 470p 560p 680p 820p 1000p 1200p 1500p 1800p 2200p 2.7n 3.3n 3.9n 4.7n 5.6n 6.8n 8.2n 10n 12n 15n 18n 22n 33n 39n 47n 56n 68n 82n 100n
	alter C2 $val_c2

    echo Running simulation {$fnb} with Ra = {$val_ra}, Cl = {$val_cl} and C2 = {$val_c2}
*	option xmu=0.495
	listing e
	TRAN 5n 250u 0 5n UIC
	* for testing, comment out the plot commands, and comment the hardcopy and shell commands.
*	plot v(sortie) v(7) v(grille) xlabel "Cl = $val_cl C2 = $val_c2" title "Cl = $val_cl C2 = $val_c2"
	hardcopy {$fnb}cl={$val_cl}c2={$val_c2}.ps v(sortie) v(7) v(grille) xlabel "{$fnb}: Cl = $val_cl C2 = $val_c2" title "Cl = $val_cl C2 = $val_c2"
	* 330 is R4 value:
*	plot (v(1)-v(sortie))*((v(6)-v(sortie))/2.7e3) xlabel "Cl = $val_cl" title "Cl = $val_cl"
	hardcopy p{$fnb}cl={$val_cl}c2={$val_c2}.ps (168-v(sortie))*(v(1)-v(sortie))/2700 v(2) xlabel "{$fnb}: P Cl = $val_cl C2 = $val_c2" title "P and Vg2 Cl = $val_cl C2 = $val_c2"
     shell magick {$fnb}cl={$val_cl}c2={$val_c2}.ps {$fnb}cl={$val_cl}c2={$val_c2}.png
*     To keep the ps files, comment that line:
     shell rm  {$fnb}cl={$val_cl}c2={$val_c2}.ps
     shell magick  p{$fnb}cl={$val_cl}c2={$val_c2}.ps  p{$fnb}cl={$val_cl}c2={$val_c2}.png
*	And that line:
     shell rm p{$fnb}cl={$val_cl}c2={$val_c2}.ps

    * populate index file
    * for testing comment the echo calls.
    echo "{$fnb}cl={$val_cl}c2={$val_c2}.png" >> index.txt
    echo "p{$fnb}cl={$val_cl}c2={$val_c2}.png" >> index.txt
    * increment file number
    let filenb = $&filenb + 1
    set fnb = $&filenb
    end
end

.endc
