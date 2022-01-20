DELETE FROM `locales_creature_text` WHERE `entry` IN
(951,
1543,
1544,
1568,
2532,
2533,
3511,
3512,
3513,
3518,
3937,
25462,
34519,
34520,
34365,
38895,
42937,
49230,
49231,
49337,
49422,
49423,
49424,
49874,
49869,
50039,
50372,
50374,
50414);

INSERT INTO `locales_creature_text` (`entry`, `text_group`, `id`, `text_loc8`, `text_female_loc8`) VALUES
-- 951
(951, 0, 0, "ДА ИСЦЕЛИТ ТЕБЯ СВЕТ!", ""),
(951, 0, 1, "НЫНЕ ВОЗЛАГАЮ НА ТЕБЯ РУКИ!", ""),
(951, 0, 2, "Да озарит тебя Свет!", ""),
(951, 1, 0, "Исцелись, $gбрат:сестра;!", ""),
(951, 1, 1, "ВОЗВРАЩАЙСЯ В СТРОЙ, $GБРАТ:СЕСТРА;!", ""),
-- 1543
(1543, 0, 0, "|3-3(%s) можно ловить!", ""),
-- 1544
(1544, 0, 0, "|3-3(%s) можно ловить!", ""),
-- 1568
(1568, 0, 0, "Посмотрим... Вот, гляди, есть тело, челюсть которого тебе отлично подойдет...", ""),
(1568, 1, 0, "Вот так отлично. Если оно снова развалится, приходи еще раз.", ""),
-- 2532
(2532, 0, 0, "", "Ха-ха! Твоя горилла у меня!"),
(2532, 0, 1, "", "Посмотрим, сможет ли твоя горилла прыгнуть через парк!"),
(2532, 0, 2, "", "Твоя горилла у меня! Ля-ля-ля!"),
(2532, 0, 3, "", "Интересно, сколько раз можно повернуть эти шестеренки?"),
(2532, 0, 4, "", "Если хочешь получить ее обратно, падай на четвереньки и умоляй меня... словно обезьяна!"),
(2532, 0, 5, "", "Ну что, кто из нас плакса? Ты плакса!"),
(2532, 0, 6, "", "Малыш хочет свою игрушку!"),
(2532, 0, 7, "", "Ой!"),
-- 2533
(2533, 0, 0, "Нечестно! Отдай мою гориллу!!!", ""),
(2533, 0, 1, "Отдай мою Прыг-скок!", ""),
(2533, 0, 2, "Не ломай мою Прыг-скок! Это нечестно!", ""),
(2533, 0, 3, "А-А-А-А-А!!!", ""),
(2533, 0, 4, "Злюка! Все маме расскажу!", ""),
(2533, 0, 5, "Хватит выкручивать ей ноги! Ты ее сломаешь!", ""),
(2533, 0, 6, "Не трогай ее!", ""),
(2533, 0, 7, "Хватит! Ты ему ноги выдернешь!", ""),
-- 3511
(3511, 0, 0, "Зачем нам учить всю эту ерунду?", ""),
-- 3512
(3512, 0, 0, "Правда, что здесь обучают паладинов?", ""),
-- 3513
(3513, 0, 0, "", "А это Собор Света – центр духовного просвещения Штормграда."),
(3513, 1, 0, "", "Да, это так. В стенах Храма учатся и постигают истину и жрецы, и паладины."),
(3513, 2, 0, "", "Дети, если вы угомонитесь и пойдете за мной, мы с вами осмотрим цитадель самого короля Вариана Ринна."),
(3513, 3, 0, "", "А это – крепость Штормграда. Она построена на руинах замка, разрушенного Ордой во время первой Великой войны."),
(3513, 4, 0, "", "Когда Орда была сокрушена, люди вернулись сюда и начали отстраивать наш великий город."),
(3513, 5, 0, "", "Ну хорошо... пойдем на Аллею Героев, к памятнику величайшим героям двух великих войн. Не отставайте."),
(3513, 6, 0, "", "Не правда ли, восхитительно, дети? Каждого, кто входит в город, встречают бдительные взгляды наших величайших героев."),
(3513, 7, 0, "", "Сердце замирает... Дети, когда мы вернемся в школу, каждый из вас сделает доклад об одной из этих легендарных личностей."),
(3513, 8, 0, "", "Посмотрите еще раз, а потом мы с вами отправимся на соборный двор и увидим великий Собор Света."),
-- 3518
(3518, 0, 0, "Свежевыпеченный хлеб!", ""),
(3518, 0, 1, "Свежий хлеб!", ""),
(3518, 0, 2, "Горячий, вкусный хлеб!", ""),
(3518, 0, 3, "Хлеб, батоны, булочки! Только что из печи!", ""),
-- 3937
(3937, 0, 0, "", "Свежий хлеб, сегодня утром испекла."),
(3937, 0, 1, "", "Кому свежего хлебушка!"),
(3937, 0, 2, "", "Свежий хлеб!"),
(3937, 0, 3, "", "Стража! На помощь!"),
-- 25462
(25462, 0, 0, "Все, что составляет мою сущность: злость, безжалостность, отмщение – я вкладываю в тебя, достойнейший рыцарь. Я даровал тебе бессмертие, ибо тебе суждено стать вестником новой, темной эры Плети.", ""),
(25462, 1, 0, "Узри же земли, лежащие перед тобой. Видишь ли ты, как Алый орден тщетно пытается разрушить созданное нами? Видишь батальоны Последней Надежды, бросающие вызов войскам Плети в Чумных землях? Все они должны поплатиться за свое упрямство.", ""),
(25462, 2, 0, "Ты станешь моим возмездием, и страшен будет удел тех, кто станет у тебя на пути. Иди же и взгляни в лицо своей судьбе, мой рыцарь смерти.", ""),
-- 34519
(34519, 0, 0, "Отдай игрушку!", ""),
(34519, 1, 0, "Ну хватит!", ""),
(34519, 2, 0, "Мы пожалуемся на тебя попечительнице!", ""),
-- 34520
(34520, 0, 0, "Догони меня, если сможешь, длинноязыкий!", ""),
-- 34365
(34365, 0, 0, "", "Дети, успокойтесь! Если будете себя так вести – никто не захочет вас усыновить."),
-- 38895
(38895, 0, 0, "", "Нет. Ты лжешь! Мой отец защитит меня!"),
(38895, 0, 1, "", "Ты не понимаешь... я не могу превратиться в нежить! Только не я!"),
-- 42937
(42937, 0, 0, "Орк убивать |3-6($r)!", "Орк убивать |3-6($r)!"),
(42937, 0, 1, "Черная гора захватить лес!", "Черная гора захватить лес!"),
(42937, 0, 2, "Виноград был ОЧЕНЬ ВКУСНЫЙ!", "Виноград был ОЧЕНЬ ВКУСНЫЙ!"),
(42937, 0, 3, "Моли о пощаде!", "Моли о пощаде!"),
(42937, 0, 4, "Сожру тебя!", "Сожру тебя!"),
-- 49230
(49230, 0, 0, "ААААА! Я чудовище, не смотри на меня!", ""),
(49230, 0, 1, "Это кого ты $gназвал:назвала; чудовищем? $gСам:Сама; ты чудовище! А я просто однажды умер.", ""),
-- 49231
(49231, 0, 0, "Валдред Морай для исполнения обязанностей прибыл!", ""),
(49231, 0, 1, "Понятно. Ну что же, тогда за работу, $n! Мы нужны Темной Госпоже, не так ли?", ""),
-- 49337
(49337, 0, 0, "Снова здравствуй.", ""),
(49337, 1, 0, "Я знаю дорогу в Похоронный Звон. Иди за мной!", ""),
(49337, 2, 0, "Хорошо, что ты еще здесь. А где же страж смерти Салтен?", ""),
(49337, 3, 0, "А, вот он.", ""),
(49337, 4, 0, "Пойдем, $n. Салтен сказал, что там есть тела.", ""),
(49337, 5, 0, "Кажется, я вижу впереди тела. Давай, $n! Ты будешь искать и отбиваться. Я – нести.", ""),
-- 49422
(49422, 0, 0, "Я убью тебя!", "Я убью тебя!"),
(49422, 0, 1, "Посмотри, что они со мной сделали!", "Посмотри, что они со мной сделали!"),
(49422, 0, 2, "Кто я?", "Кто я?"),
(49422, 1, 0, "%s впадает в исступление!", "%s впадает в исступление!"),
-- 49423
(49423, 0, 0, "Я убью тебя!", "Я убью тебя!"),
(49423, 0, 1, "Посмотри, что они со мной сделали!", "Посмотри, что они со мной сделали!"),
(49423, 0, 2, "Кто я?", "Кто я?"),
-- 49424
(49424, 0, 0, "ААААА! Я чудовище, не смотри на меня!", ""),
-- 49874
(49874, 0, 0, "Орк убивать |3-6($r)!", "Орк убивать |3-6($r)!"),
(49874, 0, 1, "Черная гора захватить лес!", "Черная гора захватить лес!"),
(49874, 0, 2, "Виноград был ОЧЕНЬ ВКУСНЫЙ!", "Виноград был ОЧЕНЬ ВКУСНЫЙ!"),
(49874, 0, 3, "Моли о пощаде!", "Моли о пощаде!"),
(49874, 0, 4, "Сожру тебя!", "Сожру тебя!"),
-- 49869
(49869, 0, 0, "ПОМОГИ МНЕ!", ""),
(49869, 0, 1, "Излечи меня!", ""),
(49869, 0, 2, "Излечи меня, брат!", ""),
(49869, 0, 3, "Пакстон, приди мне на помощь и исцели меня!", ""),
(49869, 1, 0, "Идите сюда, чудовища! Мы с вами расправимся!", ""),
(49869, 1, 1, "Я прикончу еще сотню ваших боевых воргов!", ""),
(49869, 1, 2, "Будьте начеку! Поблизости орки и ворги!", ""),
(49869, 1, 3, "Пора вас отправить вслед за вашими грязными псами!", ""),
(49869, 1, 4, "Ваши ворги бессильны перед военной мощью Штормграда!", ""),
-- 50039
(50039, 0, 0, "Мы убьем любого за разумное вознаграждение!", "Мы убьем любого за разумное вознаграждение!"),
(50039, 0, 1, "Сейчас мы вас укокошим! Прощайтесь с жизнью!", "Сейчас мы вас укокошим! Прощайтесь с жизнью!"),
(50039, 0, 2, "УМРИ!", "УМРИ!"),
(50039, 0, 3, "Мы сожжем это место дотла!", "Мы сожжем это место дотла!"),
-- 50372
(50372, 0, 0, "", "Восстань из могилы и послужи Темной госпоже!"),
(50372, 0, 1, "", "Во имя Сильваны, королевы банши, я преподношу тебе этот дар!"),
(50372, 0, 2, "", "Пробудись от вечного сна и присоединись к своим братьям!"),
(50372, 0, 3, "", "Проснись, спящий, ибо тебя ждет новая жизнь!"),
(50372, 0, 4, "", "Вы вернулись к жизни. Теперь вы будете служить королеве банши."),
-- 50374
(50374, 0, 0, "Что... что со мной происходит? Что вы со мной сделали?", ""),
(50374, 1, 0, "Я должен быть мертв, и я стану мертвым!", ""),
(50374, 2, 0, "Я никогда не просил об этом! Оставьте меня в покое!", ""),
(50374, 3, 0, "Что это за магия, которая может отводить когтистую руку смерти?", ""),
(50374, 4, 0, "Если королева банши дала мне этот шанс, я с радостью буду служить.", ""),
(50374, 5, 0, "Это деяния леди Сильваны?", ""),
(50374, 6, 0, "Зачем это леди Сильване?", ""),
(50374, 7, 0, "Я... Я не помню... Зачем ты это $gсделал:сделала;?", ""),
(50374, 8, 0, "%s кончает жизнь самоубийством.", ""),
(50374, 9, 0, "%s приходит в ярость, превращается в безмозглого зомби и убегает.", ""),
(50374, 10, 0, "%s уходит к казармам.", ""),
-- 50414
(50414, 0, 0, "Сп-п-пасибо, Г-г-гробовщик.", "");