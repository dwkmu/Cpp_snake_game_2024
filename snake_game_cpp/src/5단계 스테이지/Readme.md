<img width="699" alt="image" src="https://github.com/dwkmu/Cpp_snake_game_2024/assets/144864405/1f170790-d916-4974-b912-0d12d27d37e1">
(이미지는 테스트를 위해 난이도를 낮게 설정하였습니다.)

5.23
현재 SnakeGame.cpp의 delay와 cou 조건을 변경해 게임 속도를 조절한 상태입니다.
2,3,4단계 맵 변경필요합니다. (스테이지 1은 변경 적용되어 있음)
FatalCollision의 조건(maxlenght, maxheight) 변경하였습니다 (게이트 진입시 게임오버 방지)
------------------------------------------------------
SnakeGame.h
------------------------------------------------------
CurrentStage: 현재 스테이지 저장 후 맵을 설정하기 위한 변수

GameWin : 게임 승리 시 종료조건을 위한 bool 타입 변수
poisonN, gateN, grothN, bodylen : int타입, 미션 및 스코어보드에 띄우는 변수
InitStage() : 스테이지 변경 시 초기화를 위해 기존 SnakeGame::SnakeGame()을 변경하였습니다.
gateMissionClear, grothMissionClear, poisonMissionClear, bodylenMissionClear :미션 성공여부

NextStage() : 각 미션 성공 시 다음 스테이지로 이동, 각 변수 InitStage()를 통한 초기화

-----------------------------------------------------------------------
SnakeGame.cpp
-----------------------------------------------------------------------

mvprintw() 를 통해 게임화면 옆 스코어보드, 미션보드 출력하여 5단게 구현했습니다.
GetsPoison, GetsGrowth 시, gate passing 시에 스코어보드에 띄우는 변수 값 ++하여 출력했습니다.

NextStage()에서 currentStage가 3일 때 게임 승리조건 추가하여 게임 승리 시에 you win 메시지를 띄웠습니다.
NextStage()에서 다음 단계로 넘어갈 때 currentStage ++를 통해 스테이지를 변경하고, 각 변수 초기화했습니다.
