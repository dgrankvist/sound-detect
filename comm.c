#include "comm.h"
#include <stdio.h>		// sprintf()
#include <math.h>		// sqrt()
#include <curl/curl.h>	// libcurl

// This function takes in RMS value of 1 second, each is calculated by 16000/80 = 200 samples,
// but the function will recalculate 8 pieces of RMS values, each corresponding to 2000 samples
// or 125ms of sound.

/*
 * Function definition of sendToServer. Takes array of the 80 original RMS values, calculates
 * 8 RMS values from these and uses curl to send these to a server defined in comm.h with HTTP
 * POST request.
 * Input argument: double r80[]: 80 rms sound values
 * Output argument: none
 */
void sendToServer(double r80[]){
	double r8[8], sum;
	int i, j;	// loop counters
	CURL *curl;
	CURLcode res;
	char post[1000];

	for(i=0; i<8; i++){		// to calculate 8 pieces of fast values
		sum = 0;			// initialize the sum
		for(j=0; j<10; j++){	// sum 10 pieces of rms_80
			sum += r80[j+i*10]*r80[j+i*10]*200;
		}
		r8[i] = sqrt(sum/2000);
	}
	// prepare post data
	sprintf(post, "data=%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f", 
			r8[0], r8[1], r8[2], r8[3], r8[4], r8[5], r8[6], r8[7]);
	// send data
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if(curl){
		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n", 
					curl_easy_strerror(res));
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
