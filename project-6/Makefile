all: parta partb partc partd

parta:
	gcc parta.c -o parta -g -pthread

partb:
	gcc partb.c -o partb -g -pthread

partc:
	gcc partc.c -o partc -g -pthread

partd:
	gcc partd.c -o partd -g -pthread

clean:
	rm -f parta partb partc partd

run:all
	./parta;./partb;./partc;./partd;

runa:parta
	./parta

runb:partb
	./partb

runc:partc
	./partc

rund:partd
	./partd
