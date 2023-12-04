all: 
	gcc camera.c -g -o cam
	gcc drone.c -g -o drone
	gcc webCam.c -g -o web
	gcc camera_color_resolution.c -g -o camcolres
	gcc drone_color_resolution.c -g -o drocolres
	gcc webCam_color_resolution.c -g -o webcolres
	gcc object_detection.c -o obj -lSDL2 -lSDL2_image
	gcc camera_encoding_compression.c -g -o camencom
	gcc drone_encoding_compression.c -g -o droencom
	gcc webCam_encoding_compression.c -g -o webencom
	gcc server.c -g -o server
	gcc client.c -g -o client
	
	./cam
	./drone
	./web
	./camcolres
	./drocolres
	./webcolres
	./obj
	./camencom
	./droencom
	./webencom
	./server camera_server_out.mp4 drone_server_out.mp4 webCam_server_out.mp4 2000
	./client camera_compressed.mp4 drone_compressed.mp4 webCam_compressed.mp4 127.0.0.1 2000
	mplayer -vo caca camera_server_out.mp4 drone_server_out.mp4 webCam_server_out.mp4
	
	
