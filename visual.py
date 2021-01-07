import sys
import re
from collections import OrderedDict


LOG_PATTERN = r'(\d+)\s*(\d+)\s(.*)'
STATE_DIED      = 'X'
STATE_FORK1     = '-'# 'f'
STATE_FORK2     = '-'# 'F'
STATE_EAT       = 'E'
STATE_SLEEP     = '|'
STATE_THINK     = '-'
STATE_FED_UP    = '.'
STATE_UNKOWN    = '?'

STATE_TIME_DEL  = ' '

def get_state_char(philo_msg, old_state=STATE_UNKOWN):
    if re.match(r'.*died.*', philo_msg):
        return STATE_DIED
    elif re.match(r'.*fork.*', philo_msg):
        return STATE_FORK1 if old_state != STATE_FORK1 else STATE_FORK2
    elif re.match(r'.*eat.*', philo_msg):
        return STATE_EAT
    elif re.match(r'.*sleep.*', philo_msg):
        return STATE_SLEEP
    elif re.match(r'.*think.*', philo_msg):
        return STATE_THINK
    elif re.match(r'.*fed.*', philo_msg):
        return STATE_FED_UP
    else:
        return STATE_UNKOWN


def collect_info_from_log_line(line):
    match_group = re.search(LOG_PATTERN, line).groups()
    return (int(match_group[0]), int(match_group[1]) - 1, match_group[2])


def update_philo_frame(philosophers, old_state_idx, new_state_idx):
    for idx in range(len(philosophers)):
        old_state = philosophers[idx][old_state_idx]
        if old_state == STATE_TIME_DEL:
            old_state = philosophers[idx][old_state_idx - 1]
        philosophers[idx][new_state_idx] = philosophers[idx].get(new_state_idx, old_state)
    return new_state_idx, new_state_idx + 1


def collect_philo_history(filename, philo_num):
    philosophers = list()

    for philo_idx in range(philo_num):
        philosophers.append(OrderedDict())
        philosophers[philo_idx][0] = get_state_char("think")

    with open(filename, "r") as f:
        old_state_idx = 0
        old_time = 0
        new_state_idx = 1
        for line in f:
            time_ms, philo_idx, philo_msg = collect_info_from_log_line(line)

            if philosophers[philo_idx].get(new_state_idx) or time_ms != old_time:
                old_state_idx, new_state_idx = update_philo_frame(philosophers, old_state_idx, new_state_idx)
                if time_ms != old_time:
                    for idx in range(len(philosophers)):
                        philosophers[idx][new_state_idx] = STATE_TIME_DEL
                    old_state_idx = new_state_idx
                    new_state_idx += 1
                    old_time = time_ms
            
            philosophers[philo_idx][new_state_idx] = get_state_char(philo_msg, philosophers[philo_idx][old_state_idx])

    update_philo_frame(philosophers, old_state_idx, new_state_idx)
    return philosophers


def get_philo_state_string(philo_time_dict):
    result = ""
    for state in philo_time_dict.values():
        result += state
    return result

def main(argv):

    if len(argv) != 3:
        sys.stderr.write("Invalid number of arguments\n")
        exit(1)

    philo_num = int(argv[1])
    filename = argv[2]

    philos_history = collect_philo_history(filename, philo_num)
    for philo_idx in range(len(philos_history)):
        sys.stdout.write('%3d:%s\n' % (philo_idx + 1, get_philo_state_string(philos_history[philo_idx])))


if __name__ == '__main__':
    main(sys.argv)