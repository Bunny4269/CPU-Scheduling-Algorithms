#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
};

bool compare_arrival_time(const Process &p1, const Process &p2) {
    return p1.arrival_time < p2.arrival_time;
}

void FCFS(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compare_arrival_time);

    int current_time = 0;
    for (int i = 0; i < processes.size(); ++i) {
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
    }
}

void SJF(vector<Process> &processes) {
    sort(processes.begin(), processes.end(), compare_arrival_time);

    int current_time = 0;
    for (int i = 0; i < processes.size(); ++i) {
        if (current_time < processes[i].arrival_time)
            current_time = processes[i].arrival_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
    }
}

void RoundRobin(vector<Process> &processes, int quantum) {
    int n = processes.size();
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }
    int current_time = 0;
    bool all_done = false;
    while (!all_done) {
        all_done = true;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                all_done = false;
                if (remaining_time[i] > quantum) {
                    current_time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    current_time += remaining_time[i];
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    remaining_time[i] = 0;
                }
            }
        }
    }
}

void display_results(const vector<Process> &processes) {
    cout << "PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const Process &p : processes) {
        cout << p.pid << "\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t" << p.waiting_time << "\t\t" << p.turnaround_time << endl;
    }
}

void calculate_avg_times(const vector<Process> &processes, double &avg_turnaround, double &avg_waiting) {
    double total_turnaround = 0;
    double total_waiting = 0;
    for (const Process &p : processes) {
        total_turnaround += p.turnaround_time;
        total_waiting += p.waiting_time;
    }
    avg_turnaround = total_turnaround / processes.size();
    avg_waiting = total_waiting / processes.size();
}

int main() {
    int choice, quantum;
    vector<Process> processes;
    cout << "Enter the number of processes: ";
    int n;
    cin >> n;
    processes.resize(n);
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        cout << "Enter Arrival Time and Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
    }

    cout << "Choose Scheduling Algorithm:\n";
    cout << "1. First Come First Serve (FCFS)\n";
    cout << "2. Shortest Job First (SJF)\n";
    cout << "3. Round Robin (RR)\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            FCFS(processes);
            break;
        case 2:
            SJF(processes);
            break;
        case 3:
            cout << "Enter Time Quantum for Round Robin: ";
            cin >> quantum;
            RoundRobin(processes, quantum);
            break;
        default:
            cout << "Invalid choice";
            return 1;
    }

    display_results(processes);

    if (choice == 3) {
        double avg_turnaround, avg_waiting;
        calculate_avg_times(processes, avg_turnaround, avg_waiting);
        cout << "Average Turnaround Time: " << avg_turnaround << endl;
        cout << "Average Waiting Time: " << avg_waiting << endl;
    }

    return 0;
}
