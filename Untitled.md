```c
#include <stdio.h>


// 全局初始化
int global_init();

// 全局清理
void global_cleanup();



// 获取单次操作句柄
long init();

// 获取要下载的文件的文件大小
long get_download_file_length(long instance, const char *url);

// 顺序下载文件
bool download(long instance, const char *url, const char *local, long *writedlen);

// 断点式区块下载
bool download_range(long instance, const char *url, const char *local, long start, long range, long *writedlen);

// 停止当前的下载操作
bool stop_downloading(long instance);

// 清理句柄
void clear(long instance);

```

```c
#include "download.h"
#include "curl/curl.h"

typedef struct _WriteData {
	FILE *fp;
	long start;
	long wanted_len;
	long writed_len;
}UxWriteData;

static size_t write_function_with_range(void *ptr, size_t size, size_t nmemb, void *userdata) {
	size_t ret = 0;
	UxWriteData *writedata = (UxWriteData *)userdata;
	// 目前下载的区块小于期望大小
	if (writedata.writed_len < writedata.wanted_len) {
		long count = fwrite(ptr, size, nmemb, writedata.fp);
		if (count != nmemb) {
			ret = -1;
		}
		else {
			ret = size *nmemb;
			writedata.writed_len += ret;
		}
	}
	else {
		ret = -1;
	}
	
	return ret;
}


static size_t write_function_normal(void *ptr, size_t size, size_t nmemb, void *userdata) {
	size_t ret = 0;
	UxWriteData *writedata = (UxWriteData *)userdata;
	
	size_t count = fwrite(ptr, size, nmemb, writedata.fp);
	if (count != nmemb)  {
		ret = -1;
	}
	else {
		ret = size * nmemb;
		writedata.writed_len += ret;
	}
	
	return ret;

}


long global_init() {
	curl_global_init(CURL_GLOBAL_ALL);
}

long init() {
	CURL *curl = curl_easy_init();
	if(curl) {
		return (long)curl;
	}
	else {
		return 0;
	}
}

long get_download_file_length(long instance, const char *url) {
	long data_len = 0;
	
	curl_easy_setopt((CURL*)instance, CURLOPT_URL, url);
	curl_easy_setopt((CURL*)instance, CURLOPT_HEADER,1);
	curl_easy_setopt((CURL*)instance, CURLOPT_NOBODY,1);
	
	if (curl_easy_peform((CURL*)instance) == CURL_OK)
	{
		curl_easy_getinfo((CURL*)instance, CURLINFO_CONTENT_LENGTH_DOWNLOAD, &data_len);
	}
	else 
	{
		data_len = 0;
	}
	
	return data_len;
}

long download(long instance, const char *url, const char *local, long *writedlen) {
	long ret = 0;
	
	
	FILE *fp = fopen(local, "wb+");
	if (!fp)
	{
		ret = -1;
	}
	else
	{
		UxWriteData data;
		data.fp = fp;
		data.start = 0L;
		data.wanted_len = 0L;
		data.writed_len = 0L;
		
		CRUL *curl = (CURL*)instance;
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, true);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_normal);
		
		CURLCode res = curl_easy_peform(curl);
		if (res != CURL_OK)
		{
			ret = -1;
		}
	
		*writedlen = 
	}
	
	return 0;
}

long download_range(long instance, const char *url, const char *local, long start, long range, long *writedlen) {
	long ret = 0;
	
	FILE *fp = fopen(local, "wb+");
	if (!fp)
	{
		ret = -1;
	}
	else 
	{
		UxWriteData data;
		data.fp = fp;
		data.start = start;
		data.wanted_len = range;
		data.writed_len = 0L;
	
		fseek(fp, start, SEEK_SET);
	
		CRUL *curl = (CURL*)instance;
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_NOPROGRESS, true);
		curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
		curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_RESUME_FROM, start);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function_with_range);
	
		CURLCode res = curl_easy_peform(curl);
	
		if (res != CURL_OK) {
			ret = -1;;
		}
		
		*writedlen = data.writed_len;
	}
	
	return ret;
}


bool stop_download(long instance) {
	curl_easy_reset((CURL*)instance);
}

void clear(long instance) {
	curl_easy_cleanup((CURL*)instance);
}

void global_clear() {
	
}

```