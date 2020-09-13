#include <bangtal.h>

using namespace bangtal;

int main()
{
	//장면을 생성한다. 방 2개 만들기
	ScenePtr Scene1 = Scene::create("룸1", "Images/중앙대.png"); //씬포인터 형식으로 생성됨.
	//Auto Scene1 이렇게 해줘도 가능은 함, 즉 auto가 알아서 지정해줌 
	ScenePtr Scene2 = Scene::create("룸2", "Images/배경-2.png");
	ScenePtr Scene3 = Scene::create("룸3", "Images/배경-3.png");
	ScenePtr Scene3_1 = Scene::create("푸앙-1", "Images/푸앙-1.png");
	ScenePtr Scene3_2 = Scene::create("푸앙-2", "Images/푸앙-2.png");
	ScenePtr Scene3_3 = Scene::create("푸앙-3", "Images/푸앙-3.png");
	ScenePtr Scene3_4 = Scene::create("푸앙-4", "Images/푸앙-4.png");

	auto puang = Object::create("Images/푸앙이소개.png", Scene1, 230, 480);
	puang->setScale(0.7f);
	//열쇠 만들기
	auto key = Object::create("Images/열쇠.png", Scene1, 500, 70); //초기 크기가 넘 크다
	key->setScale(0.2f); //크기 조절 해주는 함수
	//열쇠를 주으면 인벤토리로 담아야함. 즉, 열쇠를 클릭하면 마우스콜백을 이용해서 인벤토리로 가져옴

	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});
	//오리배 + 옮겨진 뒤에는 위치고정하기.
	auto duck_moved = false;
	auto duck = Object::create("Images/오리배.png", Scene1, 400, 10);
	duck->setScale(0.7f);
	duck->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (duck_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				duck->locate(Scene1, 250, 10);
				duck_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				duck->locate(Scene1, 550, 10);
				duck_moved = true;
			}
		}

		return true;
		});
	//문을 생성한다. 장면생성과 비슷함.
	//홀 이미지:<a href='https://pngtree.com/so/월풀'>월풀 png from pngtree.com</a>
	auto door1_open = false;
	auto door1 = Object::create("Images/홀.png", Scene1, 945, 170);
	door1->setScale(0.06f);
	//문을 클릭하면 이동한다.
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door1_open == true) {
			Scene2->enter();
		}

		else if (key->isHanded()) {//키가 있을 때만 열수 있도록 손에 있는지 확인하는 함수를 활용
			door1_open = true;
		}
		else {
			showMessage("여의주(지구본)에 들어가려면 열쇠가 필요해!");
		}
		return true;
		});


	//두번째 방
	auto door2 = Object::create("Images/문-왼쪽-열림.png", Scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		//룸1으로 이동
		Scene1->enter();
		return 0;
		});
	
	//푸앙이들 방으로 가는 문
	auto door3_open = false;
	auto door3 = Object::create("Images/문-오른쪽-닫힘.png", Scene2, 770, 280);
	door3->setScale(0.9f);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door3_open == true) { //문이 열린 상태
			Scene3->enter();
		}
		else { //문이 닫힌 상태
			door3->setImage("Images/문-오른쪽-열림.png");
			door3_open = true;
		}
		return true;
		});


	//책장으로 문 숨기기
	auto bookshelf = Object::create("Images/책장.png", Scene2, 710, 260);
	bookshelf->setScale(0.4f);
	auto bookshelf_moved = false;
	bookshelf->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (bookshelf_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				bookshelf->locate(Scene2, 600, 260);
				bookshelf_moved = true;
			}
		}
		return true;
		});


	//1.게임패드
	auto gamepad = Object::create("Images/게임패드.png", Scene2, 280, 230, false); //초기 크기가 넘 크다
	gamepad->setScale(0.1f); 
	gamepad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		gamepad->pick();
		return true;
		});

	//상자 (암호를 풀면 상자안에 있는 것들이 보이게)
	auto  game_box_open = false;
	auto game_box = Object::create("Images/닫힌 상자.png", Scene2, 200, 100);
	game_box->setScale(0.5f);
	game_box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
	
		if (game_box_open == true) {
			gamepad->show();
			game_box->setImage("Images/열린 상자.png");
		}

		else {
			showMessage("방탈 라이브러리의 현재 버전은? ?.?.?.? (4자리)");
		}
		return true;
		});
	
	game_box->setOnKeypadCallback([&](ObjectPtr object)->bool {
		game_box_open = true;
		showMessage("박스가 열렸다!");

		return true;
		});

	//게임박스 키패드
	auto game_box_keypad = Object::create("Images/자물쇠.png", Scene2, 260, 120);
	game_box_keypad->setScale(0.2f);
	game_box_keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("0230", game_box);
		return true;
		});

	//2.졸업장
	auto diploma = Object::create("Images/졸업장.png", Scene2, 480, 230, false); //초기 크기가 넘 크다
	diploma->setScale(0.5f); //크기 조절 해주는 함수?
	diploma->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		diploma->pick();
		return true;
		});

	//상자 (암호를 풀면 상자안에 있는 것들이 보이게)
	auto  diploma_box_open = false;
	auto diploma_box = Object::create("Images/닫힌 상자.png", Scene2, 400, 100);
	diploma_box->setScale(0.5f);
	diploma_box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (diploma_box_open == true) {
			diploma->show();
			diploma_box->setImage("Images/열린 상자.png");
		}

		else {
			showMessage("2020년 여름방학에 열렸던 학위수여식 날짜는? (00(월)00(일) 4자리)");
		}
		return true;
		});

	diploma_box->setOnKeypadCallback([&](ObjectPtr object)->bool {
		diploma_box_open = true;
		showMessage("박스가 열렸다!");

		return true;
		});

	// 키패드
	auto diploma_box_keypad = Object::create("Images/자물쇠.png", Scene2, 460, 120);
	diploma_box_keypad->setScale(0.2f);
	diploma_box_keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("0826", diploma_box);
		return true;
		});

	//3. 야구
	auto baseball = Object::create("Images/야구장비.png", Scene2, 580, 230, false); //초기 크기가 넘 크다
	baseball->setScale(0.5f); //크기 조절 해주는 함수?
	baseball->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		baseball->pick();
		return true;
		});

	//상자 (암호를 풀면 상자안에 있는 것들이 보이게)
	auto  baseball_box_open = false;
	auto baseball_box = Object::create("Images/닫힌 상자.png", Scene2, 600, 100);
	baseball_box->setScale(0.5f);
	baseball_box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (baseball_box_open == true) {
			baseball->show();
			baseball_box->setImage("Images/열린 상자.png");
		}

		else {
			showMessage("예전에 대운동장이 있었지만, 지금은 그 자리에 \n경영경제/공과대를 위한 000관이 세워졌대! (3자리)");
		}
		return true;
		});

	baseball_box->setOnKeypadCallback([&](ObjectPtr object)->bool {
		baseball_box_open = true;
		showMessage("박스가 열렸다!");

		return true;
		});

	// 키패드
	auto baseball_box_keypad = Object::create("Images/자물쇠.png", Scene2, 660, 120);
	baseball_box_keypad->setScale(0.2f);
	baseball_box_keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("310", baseball_box);
		return true;
		});

	//4. 지구본
	auto earth = Object::create("Images/지구본.png", Scene2, 880, 230, false); //초기 크기가 넘 크다
	earth->setScale(0.5f); //크기 조절 해주는 함수?
	earth->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		earth->pick();
		return true;
		});

	//상자 (암호를 풀면 상자안에 있는 것들이 보이게)
	auto  earth_box_open = false;
	auto earth_box = Object::create("Images/닫힌 상자.png", Scene2, 800, 100);
	earth_box->setScale(0.5f);
	earth_box->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (earth_box_open == true) {
			earth->show();
			earth_box->setImage("Images/열린 상자.png");
		}

		else {
			showMessage("중앙대학교의 설립년도는? 4자리)");
		}
		return true;
		});

	earth_box->setOnKeypadCallback([&](ObjectPtr object)->bool {
		earth_box_open = true;
		showMessage("박스가 열렸다!");

		return true;
		});

	// 키패드
	auto earth_box_keypad = Object::create("Images/자물쇠.png", Scene2, 860, 120);
	earth_box_keypad->setScale(0.2f);
	earth_box_keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("1918", earth_box);
		return true;
		});


	//룸 3 - 푸앙이들 문이 있는 중간방
	auto door3_1 = Object::create("Images/뒤로가기.png", Scene3, 20, 630);
	door3_1->setScale(0.5f);
	door3_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene2->enter();
		return 0;
		});

	//지구본 푸앙방
	auto earth_door = Object::create("Images/문-정면.png", Scene3, 250, 90);
	earth_door->setScale(0.25f);
	earth_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		Scene3_1->enter();
		return 0;
		});

	auto earth_door_1 = Object::create("Images/뒤로가기.png", Scene3_1, 20, 630);
	earth_door_1->setScale(0.5f);
	earth_door_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		Scene3->enter();
		return 0;
		});

	//힌트
	//U 보이게
	auto U_button = Object::create("Images/U.png", Scene3_1, 550, 500, false); //초기 크기가 넘 크다
	U_button->setScale(1); //크기 조절 해주는 함수?
	U_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		U_button->pick();
		return true;
		});
	
	auto earth_Conv = Object::create("Images/대화버튼.png", Scene3_1, 520, 365);
	earth_Conv->setScale(1);
	earth_Conv->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		
		if (earth->isHanded()) {
			showMessage("내 여의주를 찾아줘서 고마워! 힌트를 줄게~");
			U_button->show();
		}
		else {
			showMessage("여의주가 사라졌어ㅠㅠ");
		}
		return true;
		});

	// 야구 푸앙
	auto baseball_door = Object::create("Images/문-정면.png", Scene3, 450, 90);
	baseball_door->setScale(0.25f);
	baseball_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene3_2->enter();
		return 0;
		});

	auto baseball_door_1 = Object::create("Images/뒤로가기.png", Scene3_2, 20, 630);
	baseball_door_1->setScale(0.5f);
	baseball_door_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene3->enter();
		return 0;
		});

	//힌트
	//C 보이게
	auto C_button = Object::create("Images/C.png", Scene3_2, 550, 500, false); //초기 크기가 넘 크다
	C_button->setScale(1); 
	C_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		C_button->pick();
		return true;
		});

	auto baseball_Conv = Object::create("Images/대화버튼.png", Scene3_2, 520, 365);
	baseball_Conv->setScale(1);
	baseball_Conv->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (baseball->isHanded()) {
			showMessage("앗 거기있었구나 고마워! 여기 힌트!");
			C_button->show();
		}
		else {
			showMessage("난 야구선수가 꿈인 푸앙이라고 해!\n근데 내 야구방망이 못봤어?");
		}
		return true;
		});

	// 게임 푸앙
	auto game_door = Object::create("Images/문-정면.png", Scene3, 650, 90);
	game_door->setScale(0.25f);
	game_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene3_3->enter();
		return 0;
		});

	auto game_door_1 = Object::create("Images/뒤로가기.png", Scene3_3, 20, 630);
	game_door_1->setScale(0.5f);
	game_door_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene3->enter();
		return 0;
		});

	//힌트
	//A 보이게
	auto A_button = Object::create("Images/A.png", Scene3_3, 550, 500, false); //초기 크기가 넘 크다
	A_button->setScale(1); 
	A_button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		A_button->pick();
		return true;
		});

	auto game_Conv = Object::create("Images/대화버튼.png", Scene3_3, 520, 365);
	game_Conv->setScale(1);
	game_Conv->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (gamepad->isHanded()) {
			showMessage("고마워..ㅎㅎ");
			A_button->show();
		}
		else {
			showMessage("내 게임패드...어딨지...");
		}
		return true;
		});

	//졸업 푸앙
	auto dplo_door = Object::create("Images/문-정면.png", Scene3, 850, 90);
	dplo_door->setScale(0.25f);
	dplo_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene3_4->enter();
		return 0;
		});

	auto dplo_door_1 = Object::create("Images/뒤로가기.png", Scene3_4, 20, 630);
	dplo_door_1->setScale(0.5f);
	dplo_door_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		Scene3->enter();
		return 0;
		});

	//힌트

	auto dplo_Conv = Object::create("Images/대화버튼.png", Scene3_4, 520, 365);
	dplo_Conv->setScale(1);
	dplo_Conv->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {

		if (diploma->isHanded()) {
			showMessage("이진법학과 \'11\'학번 김푸앙 졸업을 축하드립니다~");
		}
		else {
			showMessage("드디어 졸업한다!!!!\n졸업장만 받으면 돼!");
		}
		return true;
		});

	//진짜 탈출구
	auto open4 = false;
	auto unlocked4 = false;
	auto door4 = Object::create("Images/문-오른쪽-닫힘.png", Scene2, 990, 240);
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (open4) {
			endGame();
		}
		else if (unlocked4) {
			object->setImage("Images/문-오른쪽-열림.png");
			open4 = true;
		}
		else {
			showMessage("힌트는 책장!");
		}

		return true;
		});


	auto keypad = Object::create("Images/키패드.png", Scene2, 960, 420);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("CAU1011", door4);
		return true;
		});

	door4->setOnKeypadCallback([&](ObjectPtr object)->bool {
		unlocked4 = true;
		showMessage("철커덕!!!");

		return true;
		});

	//게임을 시작한다.
	startGame(Scene1); //생성된 장면을 넘겨받아서 시작하게 해줌
	return 0;
}
