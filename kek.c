int main() {
	const size_t win_w = 1024; // image width
	const size_t win_h = 512;  // image height
	std::vector < uint32_t >
	framebuffer(win_w * win_h, pack_color(255, 255, 255)); // the image itself, initialized to white

	const size_t map_w = 16; // map width
	const size_t map_h = 16; // map height
	const char map[] = "0000222222220000"\
                       "1              0"\
                       "1      11111   0"\
                       "1     0        0"\
                       "0     0  1110000"\
                       "0     3        0"\
                       "0   10000      0"\
                       "0   0   11100  0"\
                       "0   0   0      0"\
                       "0   0   1  00000"\
                       "0       1      0"\
                       "2       1      0"\
                       "0       0      0"\
                       "0 0000000      0"\
                       "0              0"\
                       "0002222222200000"; // our game map
	float player_x = 3.456; // player x position
	float player_y = 2.345; // player y position
	float player_a = 1.523; // player view direction
	const float fov = M_PI / 3.; // field of view

	const size_t rect_w = win_w / (map_w * 2);
	const size_t rect_h = win_h / map_h;
	for (size_t j = 0; j < map_h; j++) { // draw the map
		for (size_t i = 0; i < map_w; i++) {
			if (map[i + j * map_w] == ' ') continue; // skip empty spaces
			size_t rect_x = i * rect_w;
			size_t rect_y = j * rect_h;
			draw_rectangle(framebuffer, win_w, win_h, rect_x, rect_y, rect_w, rect_h, pack_color(0, 255, 255));
		}
	}
	for (size_t i=0; i<win_w/2; i++) { // draw the visibility cone AND the "3D" view
		float angle = player_a-fov/2 + fov*i/float(win_w/2);
		for (float t=0; t<20; t+=.05) {
			float cx = player_x + t*cos(angle);
			float cy = player_y + t*sin(angle);

			size_t pix_x = cx*rect_w;
			size_t pix_y = cy*rect_h;
			framebuffer[pix_x + pix_y*win_w] = pack_color(160, 160, 160); // this draws the visibility cone

			if (map[int(cx)+int(cy)*map_w]!=' ') { // our ray touches a wall, so draw the vertical column to create an illusion of 3D
				size_t column_height = win_h/t;
				draw_rectangle(framebuffer, win_w, win_h, win_w/2+i, win_h/2-column_height/2, 1, column_height, pack_color(0, 255, 255));
				break;
			}
		}
	}
}