1...How to find a folder:
>find . -name myota\*   ==> list out all the folders contain this name
>locate myota           ==> list out all files and folder contains this name

2...How to find all the files that contain a string
>grep -rnI khong_co_gi_quy_hon
>

3.Some functions and command need to remember:
	1/ FILE

	fopen("filename", "w/r/wb/rb")  ==> chu y khi download file thi can chon che do wb
	fwrite(const void *data, int size, int num, FILE *filestream);==> write 
	fread(const void *data, int size, int num, FILE *filestream); ==> read tu stream vao file
	fseek(FILE *file, 0, SEEK_SET) => MOVE CURSOR TO the begining of the file 
	==> IN stdio.h

	system("commands ") ==> in stdlib.h




void signalHandler(int iSignal)
{
    switch(iSignal)
    {
        case SIGUSR1:
            prevTime = cameraSecondsTimeGet();
            break;

        case SIGUSR2:
            iForcedUpgrade = 1;
            break;
    }
}

	signal(SIGUSR1, signalHandler);
	signal(SIGUSR2, signalHandler);

	while(access(NWK_NORMAL_STREAMING_STATUS, F_OK) == 0 || access(PU_STREAMING_STATUS, F_OK) == 0);// F_OK: existance test,
	if these file is exist then stay here.
	==> int access (const char *filename, int how) (unistd.h)

	memcpy
	memset
	/* clean nvconf setting before extract information */
	char  nvconf_str[_AES_NVBLOCK_SIZE_];
    memset(nvconf_str, 0, sizeof(nvconf_str));

	sscanf(cmd, "%d %d %d", &a, &b, &c) ==> doc tu cmd ra cac a, b, c
	sprintf(cmd, "$s%s%s",filepath, filename, value );
	snscanf()
	snprintf()

