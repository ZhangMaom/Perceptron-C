A simple perceptron 

Author: Maomao Zhang
Email: 2908642732@qq.com

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define INPUT_VECTOR_LENGTH 5
#define INSTANCES_LENGTH 4

struct instance{
	float input_vector[INPUT_VECTOR_LENGTH];
	
	// label equal to 1 or -1
	int label;
};

void Perceptron(struct instance* instances, int epoch, float learning_rate)
{
	int i = 0;
	float weight[INPUT_VECTOR_LENGTH] = {0}, bias = 0;
	
	// initialize weight and bias
	srand(time(NULL));
	for(i = 0; i < INPUT_VECTOR_LENGTH; i++){
		weight[i] = (rand() % 10)*0.1;
	}
	
	int count = 0, index = 0;
	float prediction = 0;
	
	while(count < epoch){
		prediction = 0;
		
		// prediction = weight * input + bias
		for (i = 0; i < INPUT_VECTOR_LENGTH; i ++)
			prediction += instances[index].input_vector[i]*weight[i];
		prediction += bias;
		
		// loss = max(-label * (weight * input + bias), 0)
		// update weight and bias when loss is no less than 0
		// weight_update = weight + learning_rate*input*label
		// bias_update = bias + learning_rate*label
		if(prediction * instances[index].label <= 0){
			for (i = 0; i < INPUT_VECTOR_LENGTH; i ++)
				weight[i] += learning_rate*instances[index].label*instances[index].input_vector[i];
			
			bias += learning_rate*instances[index].label;
		}
		
		printf("%d    weight: ", count);
		for(i = 0; i < INPUT_VECTOR_LENGTH; i ++){
			printf("%f ", weight[i]);
		}
		printf(" bias: %f", bias);
		printf("instances: %d label: %d prediction: %f\n", index, instances[index].label, prediction);
		
		count ++;
		index ++;
		if(index == INSTANCES_LENGTH)
			index = 0;			
	}
}

int main()
{
	int epoch = 100;
	float learning_rate = 0.01;
	struct instance instances[INSTANCES_LENGTH] = {{{1,1,1,1,1},1},{{-1,-1,-1,-1,-1},-1},{{1,-1,1,1,-1},1},{{-1,1,-1,-1,1},-1}};
	Perceptron(instances, epoch, learning_rate);
	return 0;
 } 
