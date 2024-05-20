1단계 맵4개 구현은 해났으나 1개 뺴고 3개맵은 생긴게 똑같음, 추후 만들겠습니다. stage에 값을 0~3 으로 넣으면 0,1,2,3 총 4개의 맵이 나옴

2단계 스네이크 게임 구현, 0.25초 마다 1틱씩 움직이며(수정가능) 방향키를 눌렀을떄 스네이크가 해당방향으로 진행경로를 바꿈, 벽 이나 장애물에 부딪히면 게임오버 또한 자신의 몸통이랑 부딪혀도 게임오버 

3단계 성장, 감소 아이템 : 아이템을 먹으면 성장하거나 줄어듬, 먹으면 랜덤한곳에 새로 생성되며, 5초동안 못먹을시 기존위치 아이템은 사라지고 새로운 위치에 아이템이 새로 생김, 감소 아이템을 많이먹어 크기가 3이하가 되면 게임오버, 아이템이 장애물이나, 뱀이 있는 위치에 생성되지 않음 




5월 20일
맵4개 만들었습니다. 
SnakeGame.cpp 파일 21번째줄
	snake_map = new SnakeMap(0); 
여기서 0을 0,1,2,3 중 아무거나 넣으면 맵 바뀝니다! 

#####map1
<img width="367" alt="map1" src="https://github.com/dwkmu/Cpp_snake_game_2024/assets/84307876/a7408b32-8d79-445a-8e7c-53d4e9c7c61f">

####map2
<img width="372" alt="map2" src="https://github.com/dwkmu/Cpp_snake_game_2024/assets/84307876/411eb4a5-d127-48ee-a7fa-edcf11028621">

####map3
<img width="372" alt="map3" src="https://github.com/dwkmu/Cpp_snake_game_2024/assets/84307876/633ab1b9-07c9-4de0-be89-6919d6169f62">

####map4
<img width="373" alt="map4" src="https://github.com/dwkmu/Cpp_snake_game_2024/assets/84307876/2cd351b1-4a7e-4e9e-b6ed-07c6c83dfd8c">
