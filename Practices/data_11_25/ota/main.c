#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/stat.h>
#include <curl/curl.h>
#include <curl/easy.h>
//This callback function gets called by libcurl as soon as there is data received that needs to be saved. ptr points to the 
//delivered data, and the size of that data is size multiplied with nmemb.
//If this callback is not set, libcurl instead uses 'fwrite' by default.
//The the write_data is a callback function must match this prototype

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE* stream){
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

int read_file_by_line(char *path, char buff, line_num, int size);
int checkout_analytic_version(void);
void download_file(char *url, char *filepath);

int main(void){
	struct stat st = {0};

	//check neu khong co folder /mnt/cache/fwupgrade thi tao moi
	if(stat("/mnt/cache/fwupgrade", &st) == -1){
		mkdir("/mnt/cache/fwupgrade", 0777);
	}

	while(access("tmp/normal_streaming", F_OK)==0 || access("tmp/pu_streaming", F_OK) == 0);//doi o day cho den khi khong co app streamming va pu streamming

	//checkout_analytic_version();


	//ota_check_and_download();



	return 0;
}

int checkout_analytic_version(void){
	int sys_major = 0, sys_minor = 0, sys_revision = 0;
	char info_filename[27] = {0};
	char conf_filename[27] = {0};
	char buf[128];
	char sServerURL[64] = {0};
	char url[124] = {0};
	char info_filepath[124]={0};

	// get firmware version
	nvram_param_read("devinfo.fwver", buf);
	sscanf(buf, %d %d %d,&sys_major, &sys_minor, &sys_revision);
	// Generate downloading file: analytic_log_xx.xx.xx.conf, analytic_info_xx.xx.xx.info
	snprintf(info_filename, sizeof(info_filename), "analytic_log_%02d.%02d.%02d.info", sys_major, sys_minor, sys_revision);
	snprintf(conf_filename, sizeof(conf_filename), "analytic_dev_%02d.%02d.%02d.conf", sys_major, sys_minor, sys_revision);

	//Download zlog information file
	nvram_param_read("server.ota", sServerURL);//sServerURL = "ota.hubble.in"
	strcpy(sServerURL + strlen(sServerURL), "/ota1/0335_patch");//sServerURL = "ota.hubble.in/ota1/0335_patch"

	//download file analytic_log_xx.xx.xx.infor
	snprintf(url, sizeof(url), "%s/%s", sServerURL, info_filename);// url=ota.hubble.in/ota1/0335_patch/analytic_log_xx.xx.xx.infor
	snprintf(info_filepath, sizeof(info_filepath, "/tmp/%s", info_filename);//info_filepath="/tmp/analytic_log_xx.xx.xx.infor"
	download_file(url, info_filepath);
	
}

int read_file_by_line(char *path, char buff, line_num, int size){
	int ret = 0;
	FILE *fp;
	fp = fopen(path, "r");
	char ch;
	int i=0;
	if(fp != NULL){
		printf("Cannot load file %s\n", path);
		return -1;
	}
	while(line_num--){
		do{
		ch = fgetc(fp);
		buff[i] = ch;
		i++;
		if(i >= size)
			return 0;
		}while(ch !=  '\n');
		buff[i] = '\n';
	}
	return ret;
}

void download_file(char *url, char *filepath){
	CURL *curl;
	FILE *fp;
	CURLcode res;

	curl = curl_easy_init();
	// Dismiss the case of the previous posponsed downloaded file then retry to download the file again. <This case is really interesting case> **************REMARK HERE*************
	// open the file to store the downloaded file
	fp = fopen(filepath, "wb");
	curl_easy_setopt(curl, CURLOPT_URL, url);//mac dinh la http trong curl
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);//verify the peer's SSL certificate ==> disable
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);//verify the host's SSL certificate ==> disable
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 120);
	curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);
	fclose(fp);
	// Read version from local file
	if(read_file_by_line("/mnt/config/syslog.conf", current_version, 1, sizeof(current_version))!= 0){
		printf("Can't load the syslog.conf file \n");
		snprintf(current_version, sizeof(current_version), "#""%2d.%2d.%2d_%2d", 0, 0, 0, 0);
	}
	// Read version from downloaded file
	if(read_file_by_line(filepath, latest_version, 1, sizeof(latest_version)) != 0){
		printf("Can't load the download analytic_log file \n");
		return -2;
	}

}