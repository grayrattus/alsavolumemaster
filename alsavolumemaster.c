#include "alsavolumemaster.h"

int main() {
	long out;
	alsaMasterVolume(&out);
	printf("%ld", out);
}
