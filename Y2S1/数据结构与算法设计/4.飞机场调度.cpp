#include <iostream>
#include <queue>

using namespace std;

//Lane[i][1] Plane No.
//Lane[i][2] Plane Time.
//Lane[i][3] -1 = land , 1 = takeoff.
//Lane[i][4] totalTime.
//Lane[i][5] LianXu free.

int main(){
	int cntLane, landTime, takeTime;
	scanf("%d %d %d", &cntLane, &landTime, &takeTime);
	int currentTime = 0;
	int cntTake = 0, cntLand = 0;
	int totalTake = 0, totalLand = 0;
	int noLand = 5001;
	int noTake = 1;
	
	float average = 0;
	float timeWaitForLand = 0, timeWaitForTakeoff = 0;
	
	queue<int> waitLand;
	queue<int> waitTake;
	
	int Lane[100][100] = {0};
	
	while (cntTake >= 0 && cntLand >= 0){
		printf("Current Time: %4d\n", currentTime);
		for (int i = 1; i <= cntLane; i++){
			if (Lane[i][3] == -1 && Lane[i][2] % landTime == 0){
				Lane[i][1] = 0;
				Lane[i][2] = 0;
				printf("runway %02d is free\n", i);
			}
			else if (Lane[i][3] == 1 && Lane[i][2] % takeTime == 0){
				Lane[i][1] = 0;
				Lane[i][2] = 0;
				printf("runway %02d is free\n", i);
			}			
		}

		scanf("%d %d", &cntLand, &cntTake);
		for (int i = 0; i < cntLand; i++){
			waitLand.push(noLand);
			totalLand++;
			noLand++;
		}
		for (int i = 0; i < cntTake; i++){
			waitTake.push(noTake);
			totalTake++;
			noTake++;
		}
		for (int i = 1; i <= cntLane; i++){
			if (waitLand.size() != 0 && Lane[i][1] == 0){
				Lane[i][1] = waitLand.front();
				Lane[i][3] = -1;
				printf("airplane %04d is ready to land on runway %02d\n", waitLand.front(), i);
				waitLand.pop();
			}
			else if (waitTake.size() != 0 && Lane[i][1] == 0){
				Lane[i][1] = waitTake.front();
				Lane[i][3] = 1;
				printf("airplane %04d is ready to takeoff on runway %02d\n", waitTake.front(), i);
				waitTake.pop();
			}
			if (Lane[i][1] != 0){
				Lane[i][2]++;
				Lane[i][4]++;
			}
		}
		
		if (waitLand.size() != 0){
			timeWaitForLand += waitLand.size();
		}
		if (waitTake.size() != 0){
			timeWaitForTakeoff += waitTake.size();
		}
		
		currentTime++;
	}
	int panduan = 0;
	while (1){
		panduan = 0;
		for (int i = 1; i <= cntLane; i++){
			if (Lane[i][1] == 0){
				panduan++;
			}
		}
		if (panduan == cntLane){
			break;
		}
		printf("Current Time: %4d\n", currentTime);
		for (int i = 1; i <= cntLane; i++){
			if (Lane[i][3] == -1 && Lane[i][2] % landTime == 0 && Lane[i][5] == 0){
				Lane[i][1] = 0;
				Lane[i][2] = 0;
				Lane[i][5] = 1;
				printf("runway %02d is free\n", i);
			}
			else if (Lane[i][3] == 1 && Lane[i][2] % takeTime == 0 && Lane[i][5] == 0){
				Lane[i][1] = 0;
				Lane[i][2] = 0;
				Lane[i][5] = 1;
				printf("runway %02d is free\n", i);
			}			
		}

		for (int i = 1; i <= cntLane; i++){
			if (waitLand.size() != 0 && Lane[i][1] == 0){
				Lane[i][1] = waitLand.front();
				Lane[i][3] = -1;
				Lane[i][5] = 0;
				printf("airplane %04d is ready to land on runway %02d\n", waitLand.front(), i);
				waitLand.pop();
			}
			else if (waitTake.size() != 0 && Lane[i][1] == 0){
				Lane[i][1] = waitTake.front();
				Lane[i][3] = 1;
				Lane[i][5] = 0;
				printf("airplane %04d is ready to takeoff on runway %02d\n", waitTake.front(), i);
				waitTake.pop();
			}
			if (Lane[i][1] != 0){
				Lane[i][2]++;
				Lane[i][4]++;
			}
		}
		
		if (waitLand.size() != 0){
			timeWaitForLand += waitLand.size();
		}
		if (waitTake.size() != 0){
			timeWaitForTakeoff += waitTake.size();
		}
		
		currentTime++;
	}
	
	currentTime--;
	printf("simulation finished\n");
	printf("simulation time: %4d\n", currentTime);
	printf("average waiting time of landing: %4.1f\n", timeWaitForLand/totalLand);
	printf("average waiting time of takeoff: %4.1f\n", timeWaitForTakeoff/totalTake);
	for (int i = 1; i <= cntLane; i++){
		printf("runway %02d busy time: %4d\n", i, Lane[i][4]);
		average += Lane[i][4];
	}
	printf("runway average busy time percentage: %4.1f\%\n", average/cntLane*100/currentTime);
	return 0;
}