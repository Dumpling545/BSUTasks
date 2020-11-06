import matplotlib.pyplot as plt
from scipy.stats import poisson, binom
import numpy as np
# параметры гипотетических распределений:
# lmbd -- для распределения Пуассона
# n_bin, pr_bin -- для биномиального распределения
lmbd = 1
n_bin = 4
pr_bin = 0.5
# выборка
X = [0, 0, 3, 1, 1, 0, 1, 1, 0, 1, 4, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 3,
     3, 1, 1, 1, 2, 0, 1, 0, 2, 1, 1, 0, 2, 0, 2, 1, 1, 0, 2, 1, 2, 0, 2,
     0, 0, 1, 0, 0, 0, 0, 1, 1, 4, 1, 2, 2, 0, 0, 0, 1, 1, 1, 1, 3, 3, 2,
     1, 2, 1, 0, 2, 1, 2, 0, 0, 1, 2, 2, 2, 0, 4, 1, 1, 2, 3, 2, 0, 1, 1,
     0, 0, 0, 2, 1, 0, 2, 0]
# размер выборки
n = len(X)
# интервалы, на которые разбита выборка: в силу особенностей выборки
# будем считать, что 0 соотвествует интервалу [0, 1),
# 1 -- интервалу [1, 2), ..., i -- интервалу [i, i + 1), ...
intervals = np.sort(np.unique(np.array(X)))
# число интервалов
k = len(intervals)
# массивы, в которых будем хранить теоритические вероятности попадания
# в соответствующий интервал для каждого распределения: p_poisson --
# для распределения Пуассона, p_binomial -- для биномиального
p_poisson = []
p_binomial = []
# массив, в i-м элементе котором будем хранить количество элементов
# выборки, попавших в [i, i + 1)
intervalFrequencies = [0.0]*len(intervals)
# циклом проходим по всей выборке
for x in X:
    # увеличиваем соответствующее количество элементов
    # в данном интервале
    intervalFrequencies[x] += 1
# циклом проходим по всем интервалам
for interval in intervals:
    # подсчитываем функцию вероятности Пуассона (1) и биномиальную (2)
    # для данного значения (интервала)
    p_poisson.append(poisson.pmf(interval, lmbd))
    p_binomial.append(binom.pmf(interval, n_bin,
                                pr_bin))
# нормируем массив с частотой попадания в интервалы
q = [nu / n for nu in intervalFrequencies]
# рисуем гистограммы
plt.subplot(1, 3, 1)
plt.title('Распределение Пуассона')
plt.bar(intervals, np.array(p_poisson))
plt.subplot(1, 3, 2)
plt.title('Биномиальное распределение')
plt.bar(intervals, np.array(p_binomial))
plt.subplot(1, 3, 3)
plt.title('Распределение выборки')
plt.bar(intervals, np.array(q))
plt.show()
# здесь объединяем интервалы, в которых находится меньше 5 элементов
threshold = 5.0 / n
i = 0
while i < len(q) - 1:
    if(q[i] < threshold):
        q[i] += q[i + 1]
        del q[i + 1]
        p_poisson[i] += p_poisson[i + 1]
        p_binomial[i] += p_binomial[i + 1]
        del p_poisson[i + 1]
        del p_binomial[i + 1]
    else:
        i += 1
i = len(q) - 1
while i > 0:
    if(q[i] < threshold):
        q[i] += q[i - 1]
        del q[i - 1]
        p_poisson[i] += p_poisson[i - 1]
        p_binomial[i] += p_binomial[i - 1]
        del p_poisson[i - 1]
        del p_binomial[i - 1]
    i -= 1
# выведем значения эмпирических вероятностей
# попадания в интервалы
print(q)
# выведем значения теоритических вероятностей попадания в
# интервалы для р. Пуассона
print(p_poisson)
# вычисляем значение статистики хи-квадрат для выборки и
# распределения Пуассона по формуле (3)
chiSquarePoisson = sum([n*(q[x] - p_poisson[x])*(q[x] - p_poisson[x]) /
                        p_poisson[x] for x in range(len(q))])
print(chiSquarePoisson)
# выведем значения теоритических вероятностей попадания
# в интервалы для биномиального р.
print(p_binomial)
# вычисляем значение статистики хи-квадрат для выборки и
# биномиального распределения по формуле (3)
chiSquareBinomial = sum([n*(q[x] - p_binomial[x])*(q[x] - p_binomial[x]) /
                         p_binomial[x] for x in range(len(q))])
print(chiSquareBinomial)
