PoolACS
=======
В данном проекте представлена модель интеллектуальной системы автоматического управления температурой бассейна.

Задача:
-------
Дан бассейн с площадью поверхности **S**. Необходимо поддерживать постанную температуру воды в бассейне и постоянный уровень жидкости. Регулирование этих параметров производится путем включения и выключения насосов с производительностью **Q = const**.

Для упрощения нахождения решения введены допущения:
- Теплообмен не происходит через стенки бассейна
- Остывание произходит без изменения объема жидкости

### Переменные:
- **LL** - пороговый уровень жидкости снизу
- **LH** - пороговый уровень жидкости сверху
- **Temp** - текущая температура жидкости
- **Tin** - температура жидкости на входе
- **Tout** - температура окружающей среды
- **TL** - пороговый уровень температуры снизу
- **TH** - пороговый уровень температуры сверху
- **C** - темплоемкость жидкости
- **K** - коэфициент остывания
- **S** - площадь бассейна
- **Q** - производительность насосов



Решение
-------
Составим график L-T и пронумеруем возможные ситуации:
![таблица состояний системы](https://github.com/SunnyWolf/PoolACS/blob/master/Screenshots/statetable.png)

Screenshots
-----------
![Основное окно](https://github.com/SunnyWolf/PoolACS/blob/master/Screenshots/1.png)


