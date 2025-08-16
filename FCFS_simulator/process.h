#ifndef PROCESS_H
#define PROCESS_H

class process
{
private:
    int arrival_time; //время выполнения
    int burst_time; // Требуемоу время для выполнения процесса
    int burst_left; // Оставшееся время выполнения процесса
    bool been_seen;
    int initial_wait;
    int total_wait;
    int pid;
public:
    process(int burst, int time, int id, int importance);
    void set_arrival(int time);
    void set_pid(int num);
    int get_arrival();
    int get_burst();
    int get_burst_left();
    void dec_burst();
    int get_initial_wait();
    int get_total_wait();
    void add_wait(int time);
    bool get_seen();
    void seen(int time);
    int get_pid();
};

#endif // PROCESS_H
