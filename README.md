# minitalk_21

Проект, демонстрирующий использование сигналов.
Цель проекта, написать две программы клиент и сервер для передачи строки символов от клиента серверу.
Процесс клиент отправляет строку процессу сервер с помощью сигналов SIG_USR1, SIG_USR2.

Данная реализация неудачна, т.к. не используется квитирование полученного сигнала. Все построено
на задержках, в надежде, что серверу хватит времени обработать сигнал и он успеет распечатать символ.
Решение скажем, так себе. Если увидите похожие решения, знайте, что это не надежно.
Запуск параллельно какого-нибудь тяжелого процесса, сломает Вам все передачу из-за
нехватки времени вывести символ или обработать сигнал.

Правильное решение на мой взгляд, использовать квитирование полученного сигнала.
т.е. сервер получив сигнал, отправляет клиенту свой сигнал о том, что сигнал клиента получен, обработан и
сервер ждет новый сигнал.

Как сделать. реализовать фукцию паузы, которая смотрит, пришел ли сигнал и если да пролетает на выход,
иначе встаем на паузу и ждем сигнал. Пришедший сигнал сорвет исполнения с паузы и программа продолжит исполнение.
Также думаю, было бы уместно в инициализации отфильтровать нужные нам сигналы SIG_USR1, SIG_USR2, чтобы 
другие сигналы не срывали паузу или предусмотреть этот момент в функции паузы. т.е. \
если исполнение сорвалось с паузы, но не получен нужный сигнал SIG_USR1, SIG_USR2 
встаем снова на паузу.
