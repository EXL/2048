static unsigned long seed;

void srand(unsigned long newseed)
{
	seed = newseed;
}

unsigned long rand (void)
{
	//crc32 ;)
	seed = seed & 1 ? (seed >> 1) ^ 0xEDB88320UL : seed >> 1;

	return seed;
}
