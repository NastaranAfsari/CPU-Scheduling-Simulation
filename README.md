## CPU Scheduling Simulation
این پروژه الگوریتم‌های زمان‌بندی **FCFS**، **SJF** و **Round Robin** را به زبان **C** پیاده‌سازی می‌کند و معیارهای میانگین زمان انتظار، میانگین زمان برگشت و میانگین زمان پاسخ را محاسبه می‌کند.
## نحوه اجرا 
1. فایل **CpuScheduling.c** را با یک کامپایلر C (مثل gcc) کامپایل کنید:
```bash
gcc CpuScheduling.c -o CpuScheduling
```

2. برنامه را اجرا کنید:
```bash
./CpuScheduling
```

## ورودی ها
- **تعداد فرآیندها**: یک عدد صحیح
- **زمان ورود و اجرا**: برای هر فرآیند، دو عدد صحیح
- **کوانتوم زمانی**: یک عدد صحیح برای Round Robin

نمونه ورودی:
```bash
Enter number of processes: 4
Enter Arrival Time and Burst Time for Process 1: 0 6
Enter Arrival Time and Burst Time for Process 2: 2 4
Enter Arrival Time and Burst Time for Process 3: 4 8
Enter Arrival Time and Burst Time for Process 4: 5 5
Enter time quantum for Round Robin: 4
```

## خروجی ها 
برای هر الگوریتم، جدولی شامل موارد زیر نمایش داده می‌شود:
- **PID**: شناسه فرآیند
- **Arrival Time**: زمان ورود
- **Burst Time**: زمان اجرا
- **Waiting Time**: زمان انتظار
- **Turnaround Time**: زمان برگشت
- **Response Time**: زمان پاسخ

نمونه خروجی:
```bash
=== FCFS ===

PID     Arrival Burst   Waiting Turnaround      Response
1       0       6       0       6               0       
2       2       4       4       8               4       
3       4       8       6       14              6       
4       5       5       13      18              13      
Average Waiting Time: 5.75
Average Turnaround Time: 11.50
Average Response Time: 5.75

=== SJF ===

PID     Arrival Burst   Waiting Turnaround      Response
1       0       6       0       6               0
2       2       4       4       8               4
3       4       8       11      19              11
4       5       5       5       10              5
Average Waiting Time: 5.00
Average Turnaround Time: 10.75
Average Response Time: 5.00

=== Round Robin (Quantum: 4) ===

PID     Arrival Burst   Waiting Turnaround      Response
1       0       6       8       14              0
2       2       4       2       6               2
3       4       8       10      18              4
4       5       5       13      18              9
Average Waiting Time: 8.25
Average Turnaround Time: 14.00
Average Response Time: 3.75
```
