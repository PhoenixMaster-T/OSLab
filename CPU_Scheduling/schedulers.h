#include <stdio.h>
#include "process.h"

void print(Process p[], int n)
{
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_response_time = 0;
	for (int i = 0; i < n; i++)
	{
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
	}
	printf("\tAverage Waiting Time   : %-2.2lf\n", 1.0 * total_waiting_time / n);
	printf("\tAverage Turnaround Time: %-2.2lf\n", 1.0 * total_turnaround_time / n);
	printf("\tAverage Response Time  : %-2.2lf\n\n", 1.0 * total_response_time / n);

	printf("\t| PID | Arrive Time | Burst Time | Priority | Return Time |  Response Time  | Waiting Time | Turnaround Time |\n");
	for (int i = 0; i < n; i++)
	{
		printf("\t| %3s |     %3d     |     %3d    |    %3d   |     %3d     |      %3d        |      %3d     |        %3d      |\n",
			   p[i].id, p[i].arrive_time, p[i].burst, p[i].priority, p[i].return_time, p[i].response_time, p[i].waiting_time, p[i].turnaround_time);
	}
	printf("\n");
}

void FCFS(Process *p, int num_process)
{
	int now = 0, counter = 0;

	while (counter < num_process)
	{
		if (now >= p[counter].arrive_time)
		{
			if (p[counter].executing == false && p[counter].tmp_burst_ > 0)
			{
				// first time executing
				p[counter].response_time = now - p[counter].arrive_time;
				p[counter].waiting_time = now - p[counter].arrive_time;
				p[counter].executing = true;
			}
			else if (p[counter].tmp_burst_ == 0)
			{
				p[counter].return_time = now;
				p[counter].turnaround_time = now - p[counter].arrive_time;
				p[counter].completed = true;
				p[counter].executing = false;

				counter += 1;
				// if finish => change to the next process
				// do not update now before updating p[counter+1].response_time ....
				continue;
			}
			p[counter].tmp_burst_ -= 1;
		}
		now += 1;
	}
}

void SJF(Process *p, int num_process)
{
	// To do ----------------------------- SJF non-preemptive algorithms----------------------------
	int now = 0, counter = 0, i = 0;
	bool isFounded = false;
	while (counter < num_process)
	{
		Process *curr = NULL;
		// find process has min brust at time now
		if (!isFounded)
		{
			int minBrust = 999;
			for (i = 0; i < num_process; i++)
			{
				if (now >= p[i].arrive_time && p[i].completed == false && p[i].burst < minBrust)
				{
					curr = &p[i];
					minBrust = curr->burst;
				}
			}
			if (curr != NULL)
			{
				//printf("id now is: %s\n", curr->id);
				isFounded = true;
			}
		}
		// if not founded, increase now 1
		if (!isFounded)
			now++;
		while (isFounded)
		{
			if (curr->executing == false && curr->tmp_burst_ > 0)
			{
				curr->executing = true;
				curr->response_time = now - curr->arrive_time;
				curr->waiting_time = now - curr->arrive_time;
			}
			else if (curr->tmp_burst_ == 0)
			{
				isFounded = false;
				curr->completed = true;
				curr->executing = false;
				++counter;
				curr->return_time = now;
				curr->turnaround_time = now - curr->arrive_time;
				break;
			}
			curr->tmp_burst_--;
			now++;
		}
	}
	// -----------------------------------
}

void Priority_Scheduling(Process *p, int num_process)
{
	//------------Priority scheduling pre-emptive with higher number presents higher priority-----------------
	int now = 0, i = 0, counter = 0;
	Process *curr = NULL;

	while (counter < num_process)
	{
		// find suitable process to execute at time now
		int priority = -1;
		for (i = 0; i < num_process; ++i)
		{
			if (now >= p[i].arrive_time && p[i].completed == false && p[i].priority > priority)
			{
				curr = &p[i];
				priority = curr->priority;
			}
		}
		if (curr->executing == false && curr->tmp_burst_ > 0)
		{
			curr->executing = true;
			curr->response_time = now - curr->arrive_time;
		}
		curr->tmp_burst_--;
		++now;
		if (curr->tmp_burst_ == 0)
		{
			curr->completed = true;
			curr->executing = false;
			++counter;
			curr->return_time = now;
			curr->turnaround_time = now - curr->arrive_time;
			curr->waiting_time = curr->turnaround_time - curr->burst;
		}
	}
	// -----------------------------------
}

void RR(Process *p, int num_process, Quantum q)
{
	// To do -----------------------------

	// -----------------------------------
}
