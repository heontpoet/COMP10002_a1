/* Tweet cleanser:
 * Removes non-alphanumeric characters from tweets
 *
 * Skeleton code written by Yi Han and Jianzhong Qi, April 2019
 *
 */

// This code is written by Ian Teh Wen Jing on the 29th of April 2019 for
// COMP10002 assignment 1
// Algorithms are fun!
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* stage numbers */
	#define STAGE_NUM_ONE 1
	#define STAGE_NUM_TWO 2
	#define STAGE_NUM_THREE 3
	#define STAGE_NUM_FOUR 4
	#define STAGE_NUM_FIVE 5
	#define STAGE_HEADER "Stage %d\n==========\n"	/* stage header format string */

#define MAX_TWEET_LENGTH 280					/* maximum length of a tweet */
#define MAX_NUM_TWEETS 100						/* maximum number of tweets */

typedef char tweet_t[MAX_TWEET_LENGTH+1];		/* a tweet */

/****************************************************************/

/* function prototypes */
void read_one_tweet(tweet_t one_tweet, int max_len, int stage);
void print_stage_header(int stage_num);
void tweet_tolower(tweet_t one_tweet);

void stage_one(tweet_t one_tweet);
void stage_two(tweet_t tweets[], int *num_tweets);
void stage_three(tweet_t tweets[], int num_tweets);
void stage_four(tweet_t tweets[], int num_tweets);
void stage_five(tweet_t tweets[], int num_tweets);

/* add your own function prototypes here */
void cleanse_tweet(tweet_t one_tweet);
void remove_asterisks(tweet_t one_tweet);
void longest_length(tweet_t tweets[],int *longest, int *length,int num_tweets);
int is_contained(tweet_t source_tweet, tweet_t target_tweet);
void int_swap(char *int1, char *int2);
void str_swap(char *str1,char *str2);
/****************************************************************/

/* main function controls all the action, do NOT modify this function */
int
main(int argc, char *argv[]) {
	/* to hold all input tweets */
	tweet_t tweets[MAX_NUM_TWEETS];
	/* to hold the number of input tweets */
	int num_tweets = 0;

	/* stage 1: reading the first tweet */
	stage_one(tweets[num_tweets]);
	num_tweets++;

	/* stage 2: removing non-alphanumeric characters */
	stage_two(tweets, &num_tweets);

	/* stage 3: removing extra asterisks and finding the longest tweet */
	stage_three(tweets, num_tweets);

	/* stage 4: finding the non-contained tweets */
	stage_four(tweets, num_tweets);

	/* stage 5: sorting the tweets */
	stage_five(tweets, num_tweets);

	/* all done; take some rest */
	return 0;
}

/* read a line of input into one_tweet */
void
read_one_tweet(tweet_t one_tweet, int max_len, int stage) {
	int i = stage, c;
	while (((c= getchar())!= EOF)&& (c!= '\n')&& (c!= '\r')&& (c!= '\0')) {
		if (i < max_len) {
			one_tweet[i++] = c;
		} else {
			printf("Invalid input line, toooooooo long.\n");
			exit(EXIT_FAILURE);
		}
	}
	one_tweet[i] = '\0';
}

/* print stage header given stage number */
void
print_stage_header(int stage_num) {
	printf(STAGE_HEADER, stage_num);
}

/****************************************************************/
/* add your code below */
// Function to remove any characters that arent digits or alphabets
void
cleanse_tweet(tweet_t one_tweet) {
	int new_size = 0,i;
	tweet_t copy;
	for (i=0; i<strlen(one_tweet); i++) {
		// Checks if the character is a digit,alphabet or asterisk
		if (isalpha(one_tweet[i])|| one_tweet[i]== '*'|| isdigit(one_tweet[i])){
			copy[new_size++] = one_tweet[i];
		}
	}
	copy[new_size]='\0';
	strcpy(one_tweet, copy);
}
// Function to remove the leading, trailing and extra asterisk between words
void
remove_asterisks(tweet_t one_tweet) {
	int new_size=0,i=0,size;
	tweet_t copy;
	size = strlen(one_tweet);
	// Skips over the leading asterisks
	while(one_tweet[i]=='*') {
		i++;
	}
	while(i<size) {
		// Checks if character is an alphabet or digit
		while (isalpha(one_tweet[i]) || isdigit(one_tweet[i])) {
			copy[new_size++]=one_tweet[i];
			i++;
		}
		// If character is an asterisk, checks if the following character is an
		// asterisk or null byte to determine if asterisk is to be copied over
		if (one_tweet[i]=='*'&& one_tweet[i+1]!= '*'&& one_tweet[i+1]!= '\0') {
			copy[new_size++]=one_tweet[i];
		}
		i++;
	}

	copy[new_size]='\0';
	strcpy(one_tweet, copy);
	/*for (i=0; i<new_size; i++) {
		one_tweet[i]=copy[i];
	}
	one_tweet[i]='\0';*/
}

// Function to find the longest tweet and its's length
void
longest_length(tweet_t tweets[],int *longest,int *length,int num_tweets) {
	int i,j=0,counter;
	// This loop determines the longest tweet by calculcationg it's length and
	// checking it against the highest value that's been found
	for(i=0;i<num_tweets;i++) {
		j=0;
		counter = 0;
		while (tweets[i][j] != '\0') {
			counter++;
			j++;
		}
		if (counter > *length) {
			*length=counter;
			*longest=i;
		}
	}
}

// Function checks if a tweet is contained within another tweet
int
is_contained(tweet_t source_tweet, tweet_t target_tweet) {
	int i=0,j=0;
	// Loop compares each individual character between the 2 tweets
	while (target_tweet[i]) {
		for(j=0;target_tweet[i++]==source_tweet[j];j++) {
			if (source_tweet[j+1]=='\0') {
				return 1;
			}
		}
	}
	return 0;
}

// swaps the pointer of 2 tweets
void
int_swap(char *int1, char *int2) {
	int tmp;
	tmp = *int1;
	*int1 = *int2;
	*int2 = tmp;
}

// swaps the tweets in the array
void
str_swap(char *str1,char *str2) {
	tweet_t temp;
	strcpy(temp, str1);
	strcpy(str1, str2);
	strcpy(str2, temp);
}

/* scan a tweet and convert all English letters into lowercase */
void
tweet_tolower(tweet_t one_tweet) {
	/* add code here to convert English letters in one_tweet into lowercase */
	int i;
	for (i=0; one_tweet[i] != '\0'; i++) {
		if(one_tweet[i] >= 'A' && one_tweet[i] <= 'Z') {
			one_tweet[i] += 32;
		}
	}
}

/* stage 1: reading the first tweet */
void
stage_one(tweet_t one_tweet) {
	int stage=0;
	/* print stage header */
	print_stage_header(STAGE_NUM_ONE);

	/* add code to call the read_one_tweet function to read the first tweet */

	read_one_tweet(one_tweet, MAX_TWEET_LENGTH, stage);

	/* add code into the tweet_tolower function
	 * to convert English letters into lowercase
	 */
	tweet_tolower(one_tweet);

	/* print result */
	printf("%s\n\n", one_tweet);
}

/* stage 2: removing non-alphanumeric characters */
void
stage_two(tweet_t tweets[], int *num_tweets) {
	/* add code for stage 2 */
	int i=0,k,stage=1;
	print_stage_header(STAGE_NUM_TWO);
	// Reads all the tweets from the input file into the array
	while(((k=getchar()) != EOF)) {
		tweets[(*num_tweets)][i]=k;
		read_one_tweet(tweets[(*num_tweets)], MAX_TWEET_LENGTH, stage);
		(*num_tweets) ++;
	}
	// This loop cleanses the tweet and converts all the uppercase letters into
	// lowercase
	for (i=0; i<(*num_tweets); i++) {
		cleanse_tweet(tweets[i]);
		tweet_tolower(tweets[i]);
		printf("%s\n",tweets[i]);
	}
	printf("\n");
}

/* stage 3: removing extra asterisks and finding the longest tweet */
void
stage_three(tweet_t tweets[], int num_tweets) {
	/* add code for stage 3 */
	int i,longest=0,length=0;
	print_stage_header(STAGE_NUM_THREE);
	// Calls upon the remove_asterisk function on each of the tweets in array
	for (i=0; i<num_tweets; i++) {
		remove_asterisks(tweets[i]);
		printf("%s\n", tweets[i]);
	}
	printf("Total: %d\n",num_tweets);
	longest_length(tweets,&longest,&length,num_tweets);
	printf("Longest: %s\n",tweets[longest]);
	printf("Length: %d\n\n",length);
}

/* stage 4: finding the non-contained tweets */
void
stage_four(tweet_t tweets[], int num_tweets) {
	/* add code for stage 4 */
	int i,j,counter,non_contained_tweets=0;
	print_stage_header(STAGE_NUM_FOUR);
	// Nested loops to iterate through the 2D array of tweets and check for the
	// contained tweets
	for (i=0;i<num_tweets;i++) {
		counter= 0;
		for (j=0;j<num_tweets;j++) {
			if (i==j) {
				//do nothing and skip the same tweets
			} else if (is_contained(tweets[i], tweets[j])) {
				break;
			} else {
				counter++;
			}
		}
		//Checks whether the tweet is not contained
		if (counter == (num_tweets-1)) {
			printf("%s\n",tweets[i]);
			non_contained_tweets++;
		}
	}
printf("Non-contained: %d\n\n",non_contained_tweets);
}

/* stage 5: sorting the tweets */
void
stage_five(tweet_t tweets[], int num_tweets) {
	/* add code for stage 5 (optional stage) */
	print_stage_header(STAGE_NUM_FIVE);
	tweet_t array_of_lengths;
	int i,j;
	// This loop creates an array containing the length of each tweet
	for(i=0;i<num_tweets;i++) {
		array_of_lengths[i]=strlen(tweets[i]);
	}
	// THis loops sorts the array of tweets and length by insertion sort
	for(i=1;i<num_tweets;i++) {
		for(j=i-1;j>=0;j--) {
			if(array_of_lengths[j+1]<array_of_lengths[j]) {
				int_swap(array_of_lengths+j,array_of_lengths+j+1);
				str_swap(tweets[j],tweets[j+1]);
			} else if(array_of_lengths[j+1]==array_of_lengths[j] &&
				        strcmp(tweets[j],tweets[j+1])>0) {
					int_swap(array_of_lengths+j,array_of_lengths+j+1);
					str_swap(tweets[j],tweets[j+1]);
			}
		}
	}
	for(i=0;i<num_tweets;i++) {
		printf("%s\n",tweets[i]);
	}
}
