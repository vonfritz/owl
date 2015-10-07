#include "case.h"

const char send_data[116] = {
	0xAA, 0xF0, 0x6E, 0x00, 0x08, 0xFE, 0x1A, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xC3, 0x01, 0xA5, 0x02, 0x00, 0x00, 0x00, 0x00,	
	0x53, 0x4D, 0x00, 0x80, 0x04, 0x80, 0xDC, 0x19, 0x2E, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x9D, 0x00, 0x6F, 0x3C,
	0x88, 0x89, 0xA2, 0x04, 0x00, 0x00, 0xDC, 0x00, 0xC1, 0x00,
	0x28, 0x00, 0x5C, 0x4A, 0x1E, 0x00, 0xC5, 0x37, 0x28, 0x00,
	0x5C, 0x4A, 0x8F, 0x65, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00,
	0xFF, 0x00, 0x80, 0x00, 0x47, 0x00, 0x64, 0x00, 0x50, 0x00,
	0xD8, 0x00, 0x50, 0x00, 0xBB, 0x00, 0x03, 0x00, 0x3C, 0x00,
	0x6F, 0x00, 0x89, 0x00, 0x88, 0x00, 0x02, 0x00, 0xFB, 0x00,
	0x01, 0x00, 0x00, 0x00, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D,
	0x4E, 0x4F, 0xA9, 0x17, 0xAA, 0x0F};

const char recv_data[20] = {0xAA, 0xF0, 0x0E, 0x00, 0x31, 0xFE, 0x00, 0x00, 0x07, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0x01, 0xAA, 0x0F};

bool test_gps(case_t *gps_case)
{
	int fd, len, i;
	char recv_data_t[20];
	
	fd = open(gps_case->nod_path, O_RDWR);
	if(fd < 0)
	{
		printf("open device %s error\n", gps_case->nod_path);
		return false;
	}
	
	len = write(fd, send_data, sizeof(send_data));
	// printf("len = %d\n", len);
	len = read(fd, recv_data_t, 20);
	// printf("len = %d\n", len);
	for(i = 0; i < 20; i++)
	{
		if(recv_data[i] != recv_data_t[i])
		{
			printf("%d : %d : %d\n", i, recv_data[i], recv_data_t[i]);
			close(fd);
			return false;
		}
	}
	close(fd);
	return true;
}