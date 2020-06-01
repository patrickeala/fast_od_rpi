all:
	g++ -I /home/patrick/Downloads/eigen-3.3.7/ decode_detections.cpp vec_tester.cpp -std=c++14 -O2 -DNDEBUG -o vec_tester
	g++ -I /home/patrick/Downloads/eigen-3.3.7/ decode_detections.cpp nms_tester.cpp -std=c++14 -O2 -DNDEBUG -o nms_tester `pkg-config --cflags --libs opencv`
run:
	./vec_tester

clean:
	rm -rf vec_tester


