# BSGarden


__Практикум по деревьям «Планировщик деревьев»__


При написании приложения использовался фреймворк _Qt_, [их сайт](https://www.qt.io/)


Требуется реализовать приложение для визуализации работы с несколькими классами деревьев поиска. Классы деревьев поиска для реализации:
1) АВЛ дерево
2) Красно-чёрное дерево
3) Декартово дерево
4) Splay дерево

Для каждого класса деревьев необходимо реализовать основные операции:
1) Добавление элемента с ключом, вводимым пользователем.
2) Добавление некоторого количества случайных элементов (количество задаёт пользователь).
3) Удаление элемента по клику.

Нет никаких ограничений на количество элементов в дереве. Все элементы являются целыми числами, представимыми в типе int64_t. Все элементы дерева поиска уникальны. В случае ввода дубликата, надо не добавлять его в дерево.

__Организация интерфейса__

Интерфейс программы должен содержать 4 вкладки – по одной на каждый класс деревьев. На каждой вкладке должно быть основное окно, в котором рисуется дерево, и кнопки/окошки для выполнения операций вставки. Операция удаления элемента должна выполняться по клику мышкой на основной экран.

Все узлы дерева должны выглядеть одинаково. Не допускается увеличивать размер узла, в связи с тем, что в нём хранится слишком длинное число. Числа должны быть записаны в узлах аккуратно. Не допускается выход чисел за границы узлов. В идеале надо использовать моноширинный шрифт, чтобы каждая цифра занимала на экране одинаковое место.

Дерево может содержать очень различное количество ключей, поэтому необходимо предусмотреть масштабирование (приблизить/отдалить). В близком положении допускается использование вертикальной и горизонтальной прокрутки.

Пользователь капризный, и хочет, чтобы среди положений дерева (ближе/дальше) существовало такое, с которым ему будет приятно работать!

Выделение узлов или записей в узлах цветом всегда приветствуется и в некоторых случаях является обязательным (например, в красно-чёрном дереве узлы должны иметь два цвета, а в декартовом дереве полезно выделять ключ и вес разными цветами). Конкретные цвета являются творческим дизайнерским решением (пользователь капризный, но любопытный, и согласен работать и с сине-зелёным, и с фиолетово-жёлтым деревом).
