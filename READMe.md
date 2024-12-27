Описание необходимых классов и их функциональности

Tool - класс, хранящий информацию об исполнителе
    TimeInterval - структура временного интервала {start, end}
    NamedTimeInterval : TimeInterval - структура именованного интервала, имя - номер операции
    vector<TimeInterval> shedule_ - изначальное расписание исполнителя
    vector<NamedTimeInterval> work_process_ - "График Ганта" с номерами операций

    optional<size_t> CanStartWork(timestamp)