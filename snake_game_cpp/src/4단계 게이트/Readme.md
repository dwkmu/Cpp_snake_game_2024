5.20 파일 기준으로 수정한 내용입니다.
5단계 구현 후에 최종적으로 파일 합쳐서
1,2,3단계 변경 내용 적용하면 될듯 합니다!
-----------------------------------------------------------------------------


SnakeMap.h

getTotalStageCount : 스테이지 개수 반환
getCurrentMap(): 2차원 current_map 반환
getPositionInfo : current_map[x][y] 반환
setCurrentMap(next_stage) : current_stage를 next_stage로 set, current_map을 totalmap[next_stage]로 변경

setPositionInfo(x,y,info) 

map_width = 30, map_height = 60, total_stage_count = 4, total_map : 맵 , current_stage =0; current_map;


SnakeGame.h

CharPosition : 뱀 위치

snake_map : 맵 설정
Growthchar , poisonchar : 아이템 표시
bEatsFruit:
bEatsPoison:
snake : charposition head에 해당

InitGameWindow : 게임창 시작
DrawWindow : 맵 index의 값에 따라 맵 그림
DrawSnake : 스네이크 구현
PositionGrowth : 아이템 획득 시 growth
PositionPoison : poison 획득 시
FatalCollision : 충돌 시 종료를 위한 bool 타입
GetsGrowth : growth 아이템 먹었을때 true 반환
GetsPoison : poison 아이템을 먹었을 떄 true 반환
MoveSnake : 키보드 이동 적용 , 이동시에 head insert 후 snake.pop_back()으로 꼬리 이동
PlayGame : loop




(추가)

게임 테스트를 위해 delay 속도 상향조정 하였습니다.

makeGate1 , makeGate2 : 새로운 gate 의 위치를 wall 중에서 선택하고, '@' 로 표시.
CharPosition temphead: 게이트 이동시 이동 가능한 방향을 선택하고, 해당 방향의 위치를 헤드로 insert함.

CharPosition finish : 마지막 이동 위치에 꼬리가 도달 시, 새로운 게이트 생성 및 기존 게이트 위치 다시 벽으로 만듦.

isPassed, isPassing bool타입 변수를 통해 게이트 생성 간격 제어

게이트는 조건을 붙여 poison, growth 아이템과 snake와 겹치지 않으며, 이동조건에 따라 방향이 결정됨.




------------------------------------------------------------------

main.cpp

게임 진행

----------------------------------------------------------

