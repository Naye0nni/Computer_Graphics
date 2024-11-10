#include <iostream>
#include <glut.h> 
#include <math.h>
#include <chrono>
#define M_PI 3.14159265358979323846
using namespace std;

float angleX_kim = 0.0f, angleY_kim = 0.0f, angleZ_kim = 0.0f; // '김'의 회전
float angleX_char = 0.0f, angleY_char = 0.0f, angleZ_char = 0.0f; // 캐릭터의 회전

void drawBox() {
    glColor3f(0.0, 0.2, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();
}
float scaleKim = 0.0f;
float angleX_g = 0.0f; float angleY_l = 0.0f;float angleZ_m = 0.0f;
float scaleFactor_m = 1.0f; float bounceR = 0.0f; float bounceSpeedR = 0.3f; int bounceDirectionR = 1; bool bouncingR = false; const float maxBounceHeightR = 1.5f;
float scaleFactor = 0.0f; float scaleDirection = 1.0f;
bool moving_kim = false; bool kimandcharacter = false;
float translation_X = 0.0f, translation_Y = 0.0f;
float bounceY = -0.13f; float bounceSpeed = 0.3f; int bounceDirection = 1; bool bouncing = false; const float maxBounceHeight = 1.5f;
void name(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(-30, 0.0, 0.5, 0.0);
    glTranslatef(0.0, 0.2, 0.0);
    glScalef(1.0+scaleKim, 1.0+scaleKim, 1.0+scaleKim);

    // 전체 변환 적용
    glRotatef(angleX_kim, 1.0, 0.0, 0.0);
    glRotatef(angleY_kim, 0.0, 1.0, 0.0);
    glRotatef(angleZ_kim, 0.0, 0.0, 1.0);

    // ㄱ 그리기
    glPushMatrix();
    glRotatef(angleX_g, 1.0, 0.0, 0.0);
    glRotatef(angleX_kim, 1.0, 0.0, 0.0);
    // ㄱ 위쪽 가로선
    glPushMatrix();
    glTranslatef(-0.3+translation_X, 0.5+ translation_Y+ bounceR, 0.0);
    glScalef(0.25+ scaleFactor+ scaleKim / 100,  0.05+ scaleKim / 100,  0.05+ scaleKim / 5);
    drawBox(); // 가로선 그리기
    glPopMatrix();

    // ㄱ 아래쪽 세로선
    glPushMatrix();
    glTranslatef(-0.1+translation_X, 0.35+ translation_Y+ bounceR, 0.0);
    glColor3f(0.5, 0.0, 0.5);
    glutSolidSphere(0.1+ scaleFactor/2+ scaleKim / 100, 100+ scaleKim/100, 100+ scaleKim/100);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1+ translation_X, 0.15+ translation_Y+ bounceR, 0.0);
    glColor3f(0.5, 0.0, 0.5);
    glutSolidSphere(0.1+ scaleFactor/2+ scaleKim / 100, 100+ scaleKim/100, 100+ scaleKim/100);
    glPopMatrix();

    glPopMatrix(); // ㄱ 변환 복원

    // 'ㅣ' 그리기
    GLUquadric* quad = gluNewQuadric();
    gluQuadricDrawStyle(quad, GLU_LINE);
    glPushMatrix();
    glColor3f(0.5, 0.8, 0.5);
    glRotatef(angleY_l, 0.0, 1.0, 0.0);
    glRotatef(angleX_kim, 0.0, 1.0, 0.0);
    glTranslatef(0.2+ translation_X, 0.6+ translation_Y, 0.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    gluCylinder(quad, 0.07+ scaleKim*2, 0.07+ scaleKim*2, 0.6+ scaleFactor+ scaleKim *2, 32, 32);
    glPopMatrix();
    gluDeleteQuadric(quad); // quadric 객체 삭제

    // 'ㅁ' 그리기
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.8); // 색상 설정
    glRotatef(angleZ_m, 0.0, 0.0, 1.0);
    glRotatef(angleX_kim, 0.0, 0.0, 1.0);

    // 위쪽 가로선
    glPushMatrix();
    glTranslatef(0.02+translation_X, bounceY+ translation_Y, 0.05);
    glScalef( 0.4+ scaleKim, 0.08+ scaleKim, 0.1+ scaleFactor+ scaleKim);
    glutWireCube(1.0);
    glPopMatrix();

    // 왼쪽 세로선
    glPushMatrix();
    glTranslatef(-0.15+ translation_X, bounceY-0.18+ translation_Y, 0.05);
    glScalef(0.1+ scaleKim, 0.3+ scaleKim, 0.1+ scaleFactor+ scaleKim);
    glutWireCube(1.0);
    glPopMatrix();

    // 오른쪽 세로선
    glPushMatrix();
    glTranslatef(0.19+ translation_X, bounceY - 0.18+ translation_Y, 0.05);
    glScalef(0.1+ scaleKim, 0.3+ scaleKim, 0.1+ scaleFactor+ scaleKim);
    glutWireCube(1.0);
    glPopMatrix();

    // 아래 가로선
    glPushMatrix();
    glTranslatef(0.02+ translation_X, bounceY-0.36+ translation_Y, 0.05);
    glTranslatef(0, 0, 0);
    glTranslatef(-0.02, 0.0, 0.0);
    glScalef( 0.4+ scaleKim, 0.08 * scaleFactor_m+ scaleKim, 0.1+ scaleFactor+ scaleKim);
    glTranslatef(0.02, 0, 0);
    glutWireCube(1.0);
    glPopMatrix();

    glPopMatrix(); // 'ㅁ' 변환 복원

    glFlush();
}

void drawEye(float x, float y, float radius, float color[3]) {
    glPushMatrix();
    glTranslatef(x, y, 0.0); // 눈 위치 조정
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(color[0], color[1], color[2]); // 색상 설정
    glVertex2f(0.0, 0.0); // 원의 중심

    int numSegments = 100; // 원의 세그먼트 수
    for (int i = 0; i <= numSegments; i++) {
        float angle = 2.0f * 3.14159f * float(i) / float(numSegments); // 각도
        float dx = radius * cosf(angle); // x좌표
        float dy = radius * sinf(angle); // y좌표
        glVertex2f(dx, dy); // 원의 각 점
    }
    glEnd();
    glPopMatrix();
}

float zPosition = 0.0f; float zDirection = 1.0f;
float shoulder = 0; float elbow = 0; int anim = 0; int surpriseAnim = 0;
float shoulder_1 = 0;
float walkAngle = 0; float walkDirection = 1; int ani = 0;
string direction = "clockwise";
float moveX = 0.0f;  float moveY = 0.0f; // X, Y축 이동
bool moving_char = false;
float lowerArmAngle = 0.0f; float upperArmAngle = 0.0f; float lowerLegAngle = 0.0f; float upperLegAngle = 0.0f;
bool isDancing = false; bool iswalking = false;
void character(void)
{
    glPushMatrix();
    glTranslatef(0.0+angleX_char, zPosition, 0.0);
    glRotatef(angleY_char, 0.0, 1.0, 0.0); // Y축 회전
    glRotatef(0,0, 0, 0);
    glRotatef(angleZ_char, 0.0, 0.0, 1.0);
    GLUquadric* quadric = gluNewQuadric();

    // Body
    glTranslatef(-0.6+moveX, -0.5+moveY, 0);
    glPushMatrix();
    glScalef(0.35, 0.4, 0.3); // 크기 조정
    glColor3f(0.5, 0.8, 0.2); // 색상 설정
    gluQuadricDrawStyle(quadric, GLU_FILL); // 채우기 스타일 설정
    glutSolidSphere(0.7f, 100, 100); // (반지름, 세그먼트, 스택)
    glPopMatrix();
    gluDeleteQuadric(quadric);


    //왼쪽 뿔
    GLUquadric* quady1 = gluNewQuadric(); // 원기둥 생성
    gluQuadricDrawStyle(quady1, GLU_LINE);
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.5); // 보라색 설정
    glTranslatef(-0.12, 0.32, 0.0); // 뿔의 위치 조정
    glRotatef(90, 1.0, 0.0, 0.5); // 원기둥을 세로로 회전
    gluCylinder(quady1, 0.0, 0.07, 0.07, 32, 32); // 원기둥 그리기
    glPopMatrix();

    gluDeleteQuadric(quady1); // quadric 객체 삭제

    //오른쪽 뿔
    GLUquadric* quady2 = gluNewQuadric(); // 원기둥 생성
    gluQuadricDrawStyle(quady2, GLU_LINE);
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.5); // 파란색 설정
    glTranslatef(0.12, 0.25, 0.0); // 오른쪽 뿔의 위치 조정 (대칭)
    glRotatef(-90, 1.0, 0.0, 0.55); // 원기둥을 세로로 회전
    gluCylinder(quady2, 0.07, 0.0, 0.07, 32, 32); // 오른쪽 뿔 그리기
    glPopMatrix();

    gluDeleteQuadric(quady2);

    float eyeRadius = 0.15f; // 눈의 반지름
    float whiteColor[3] = { 1.0, 1.0, 1.0 }; // 흰자위 색상
    float blackColor[3] = { 0.0, 0.0, 1.0 }; // 검은 눈동자 색상
    float pupilColor[3] = { 0.0, 0.0, 0.0 }; // 작은 검은 점 색상

    // 흰자위 그리기
    drawEye(0.0, 0.04, eyeRadius, whiteColor);
    // 검은 눈동자 그리기
    drawEye(0.0, 0.02, eyeRadius * 0.6f, blackColor);
    // 작은 검은 점 그리기
    drawEye(0.0, 0.01, eyeRadius * 0.4f, pupilColor);

    glPushMatrix();
    // Upper Right Arm
    glTranslatef(0.25, 0.0, 0.0);
    glRotatef(-65.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(shoulder, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(upperArmAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(shoulder_1*1.8, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.2, 0.02, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Right Lower Arm
    glTranslatef(0.2, 0.0, 0.0);
    glRotatef(-10.0, 0.0, 0.0, 1.0);
    glTranslatef(-0.05, -0.01, 0.0);
    glRotatef(shoulder/2.5, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(shoulder_1/3, 0.0, 0.0, 1.0);
    glRotatef(lowerArmAngle, 0.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(0.15, 0.02, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Right hand
    glTranslatef(0.06, 0.0, 0.0);
    glRotatef(-10.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(shoulder_1 , 0.0, 0.0, 1.0);
    glPushMatrix();
    glColor3f(0.0, 0.05, 0.01);
    glutSolidSphere(0.015,100,100);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    // Upper Left Arm
    glTranslatef(-0.25, 0.0, 0.0);
    glRotatef(65.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-lowerArmAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-shoulder_1*1.8, 0.0, 0.0, 1.0);

    glPushMatrix();
    glScalef(0.2, 0.02, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Lower Left Arm
    glTranslatef(-0.2, 0.0, 0.0);
    glRotatef(10.0, 0.0, 0.0, 1.0);
    glTranslatef(0.05, -0.02, 0.0);
    glRotatef(-upperArmAngle, 0.0f, 0.0f, 1.0f);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-shoulder_1/3, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.15, 0.02, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Left hand
    glTranslatef(-0.06, 0.0, 0.0);
    glRotatef(10.0, 0.0, 0.0, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-shoulder_1, 0.0, 0.0, 1.0);
    glPushMatrix();
    glColor3f(0.0, 0.05, 0.01);
    glutSolidSphere(0.015, 100, 100);
    glPopMatrix();
    glPopMatrix();


    glPushMatrix();
    //Upper Right Leg
    glTranslatef(0.05, -0.3, 0.0);
    glRotatef(-85.0 , 0.0, 0.0, 1.0 + walkAngle);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(upperLegAngle, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.1, 0.03, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Lower Right Leg
    glTranslatef(0.1, 0.0, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-5.0 , 0.0, 0.0, 1.0 + walkAngle);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(lowerLegAngle, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.1, 0.03, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Right feet
    glTranslatef(0.05, 0.0, 0.0);
    glRotatef(10.0, 0.0, 0.0, 1.0+ walkAngle);
    glPushMatrix();
    glColor3f(0.0, 0.05, 0.01);
    glutSolidSphere(0.015, 100, 100);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    //Upper Left Leg
    glTranslatef(-0.05, -0.3, 0.0);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(85.0 , 0.0, 0.0, 1.0 - walkAngle);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-lowerLegAngle, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.1, 0.03, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Lower Left Leg
    glTranslatef(-0.1, 0.0, 0.0);
    glRotatef(5.0, 0.0, 0.0, 1.0 - walkAngle);
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(-upperLegAngle, 0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.1, 0.03, 0.05);
    glColor3f(0.5, 0.8, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    //Left feet
    glTranslatef(-0.05, 0.0, 0.0);
    glRotatef(-10.0, 0.0, 0.0, 1.0-walkAngle);
    glPushMatrix();
    glColor3f(0.0, 0.05, 0.01);
    glutSolidSphere(0.015, 100, 100);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();
    glFlush();
}

auto lastUpdate = chrono::high_resolution_clock::now(); // 마지막 업데이트 시간 저장
void hi(void) {
    if (anim) {
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastUpdate);
        if (direction == "clockwise") shoulder += 0.05;
        else shoulder -= 0.05;
        if (shoulder >= 90) direction = "anticlockwise";
        else if (shoulder <= 0) direction = "clockwise";

        bouncing = true;
        moving_char = true;

        glutPostRedisplay();
    }
}

void walk(void) {
    if (ani) {
        walkAngle += walkDirection * 0.1; // 각도를 증가시킴
        if (walkAngle > 10) walkDirection = -1; // 최대 각도 도달 시 방향 변경
        if (walkAngle < -10) walkDirection = 1; // 최소 각도 도달 시 방향 변경

        // 캐릭터 이동
        moveX += 0.0001f; 
        moveY += 0.0001f; 

        glutPostRedisplay();
    }
}

void rotateKimAndCharacter(void) {
    // '김'을 x축을 기준으로 회전
    angleX_kim += 0.5f;
    if (angleX_kim >= 360.0f) angleX_kim -= 360.0f;

    // 캐릭터를 '김'을 중심으로 z축 회전
    angleZ_char += 0.5f;
    if (angleZ_char >= 360.0f) angleZ_char -= 360.0f;

    if (kimandcharacter) {
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastUpdate);
        if (direction == "clockwise") shoulder_1 += 0.1;
        else shoulder_1 -= 0.1;
        if (shoulder_1 >= 90) direction = "anticlockwise";
        else if (shoulder_1 <= -45) direction = "clockwise";
    }

    glutPostRedisplay(); // 화면 업데이트 요청
}

auto lastBounceUpdate = chrono::high_resolution_clock::now();
const int bounceUpdateInterval = 300;
void keepwalking(void) {
    if (iswalking) {
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastBounceUpdate);

        if (duration.count() >= bounceUpdateInterval) {
            lastBounceUpdate = now;
            if (angleX_char < 2.0f && angleX_char>0.0f) {
                angleX_char -= 0.1f;
            }

            else if (angleX_char > -2.0f && angleX_char <= 0.0f) {
                angleX_char += 0.1f;
            }
        }
        glutPostRedisplay();
    }
}


void bounce(void) {
    if (bouncing&& moving_char ==true) {
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastBounceUpdate);

        if (duration.count() >= bounceUpdateInterval) {
            lastBounceUpdate = now; 

            if (bounceY <= 0) {
                bounceY += bounceSpeed; 
                if (bounceY >= maxBounceHeight) { 
                    bounceY = maxBounceHeight; 
                }
            }
            else {
                bounceY -= bounceSpeed; 
                if (bounceY <= 0) { 
                    bounceY = 0; 
                }
            }
            glutPostRedisplay(); 
        }
    }
}
bool movingRight = true; bool scalingUp = true;
void animateKimAndGyeok() {
    auto now = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastBounceUpdate);

    if (duration.count() >= bounceUpdateInterval) {
        lastBounceUpdate = now;

        // 'ㄱ'의 크기 변화
        if (bouncingR) {
            if (bounceR <= 0) {
                bounceR += bounceSpeedR;
                if (bounceR >= maxBounceHeightR) {
                    bounceR = maxBounceHeightR;
                }
            }
            else {
                bounceR -= bounceSpeed;
                if (bounceR <= 0) {
                    bounceR = 0;
                }
            }
        }
        // '김'의 X축 이동
        if (movingRight) {
            translation_X += 0.05f; // 오른쪽으로 이동
            if (translation_X >= 1.0f) {
                movingRight = false; // 왼쪽 방향으로 전환
            }
        }
        else {
            translation_X -= 0.05f; // 왼쪽으로 이동
            if (translation_X <= 0.0f) {
                movingRight = true; // 오른쪽 방향으로 전환
            }
        }
    }
}

void updateDanceAngles() {
    if (isDancing) {
        const int bounceUpdateInterval = 50;
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastBounceUpdate);

        if (duration.count() >= bounceUpdateInterval) {
            lastBounceUpdate = now;

            lowerArmAngle = (sin(glutGet(GLUT_ELAPSED_TIME) / 300.0) * 40.0f); // 아래 팔의 움직임
            upperArmAngle = (cos(glutGet(GLUT_ELAPSED_TIME) / 300.0) * 40.0f); // 위 팔의 움직임
            lowerLegAngle = (sin(glutGet(GLUT_ELAPSED_TIME) / 300.0) * 20.0f); // 아래 다리의 움직임
            upperLegAngle = (cos(glutGet(GLUT_ELAPSED_TIME) / 300.0) * 30.0f); // 위 다리의 움직임

            zPosition += 0.01f * zDirection; // 속도 조절
            if (zPosition >= 0.7f) {
                zDirection = -1.0f; // 방향 전환
            }
            else if (zPosition <= -0.1f) {
                zDirection = 1.0f; // 방향 전환
            }
            glutPostRedisplay();
        }
    }

    
}

bool updatescaling = false;
float scaleSpeedKim = 0.02f;

void updateScale() {
    if (updatescaling) {
        const int bounceUpdateInterval = 50;
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(now - lastBounceUpdate);

        if (duration.count() >= bounceUpdateInterval) {
            lastBounceUpdate = now;
            // '김' 전체 스케일링 조정
            scaleKim += scaleSpeedKim;
            if (scaleKim > 0.3f || scaleKim < -0.15f) {
                scaleSpeedKim = -scaleSpeedKim;
            }
            glutPostRedisplay();
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        
        // 캐릭터의 회전
    case 'b': angleY_char += 15.0f; walkDirection -= 0.1; break;
        // '김',character 의 회전
    case 'x': kimandcharacter = true; break;
        // '김',character 회전 멈춤
    case 'v':kimandcharacter = false; break;
        // '김'의 Y축 회전
    case 'y': angleY_kim += 15.0f; break;
        // '김'의 다른 속도로 확대 축소
    case 'z': updatescaling = true; break;
        //김 다른 속도로 확대 축소 멈춤
    case 'd':updatescaling = false; break;
        // '김'의 대각선 증가
    case 'c': translation_X += 0.1f; translation_Y += 0.1f; break;
        // 캐릭터의 크기 증가
    case 's': glScalef(1.1, 1.1, 1.1); break;
        // 캐릭터의 크기 감소
    case 'f': glScalef(0.9, 0.9, 0.9); break;
        // 캐릭터 오른쪽 이동
    case 'g': iswalking = true; break;
        // 캐릭터 왼쪽 이동
    case 'j': iswalking=false; break;
        //캐릭터 인사
    case 'h':anim = 1; break;
        //캐릭터 인사 멈춤
    case 'i':anim = 0; bouncing = false; break;
        //캐릭터 걸음
    case 'w': ani = 1; break;
        //캐릭터 걸음 멈춤
    case 'l': ani = 0; break; 
        //ㅁ 바운스
    case 'q': bouncing = true; moving_char = true; bounceDirection *= -1; break;
        //ㅁ 바운스 멈춤
    case 'p':bouncing = false; moving_char = false; break;
        //ㄱ 움직임, 김 좌우 이동
    case 'r':bouncingR = true; break;
        //ㄱ 움직임, 김 좌우이동 멈춤
    case 't':bouncingR = false; break;
        //ㅁ fixed point scaling
    case 'a':scaleFactor_m += 0.1f; break;
        //ㄱ,ㅣ,ㅁ 모두 다르게 회전
    case 'u':angleX_g += 5.0f; angleY_l += 5.0f; angleZ_m += 5.0f; break;
        //캐릭터 탈춤
    case 'e': isDancing = !isDancing;  break;
        //캐릭터 탈춤 멈춤
    case 'k':isDancing = false; lowerArmAngle = 0.0f; upperArmAngle = 0.0f; lowerLegAngle = 0.0f;upperLegAngle = 0.0f;
        break;
        //김 scale
    case 'o':scaleFactor += 0.01f; break;
        
    default: break;
    }
    glutPostRedisplay();
}

void Idle(void) {
    if (bouncing) {
        bounce();
    }

    if (bouncingR) {
        animateKimAndGyeok();
    }

    if (anim) {
        if (direction == "clockwise") shoulder += 0.03;
        else shoulder -= 0.03;
        if (shoulder >= 90) direction = "anticlockwise";
        else if (shoulder <= 0) direction = "clockwise";
        hi();
    }
    if (ani) {
        walk(); // 걷기 애니메이션 함수 호출
    }

    if (isDancing) {
        updateDanceAngles();
    }

    if (kimandcharacter) {
        rotateKimAndCharacter();
    }

    if (updatescaling) {
        updateScale();
    }

    if (iswalking) {
        keepwalking();
    }
    glutPostRedisplay();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    name();
    glPopMatrix();

    glPushMatrix();
    character();
    glPopMatrix();
    glFlush();

    glutSwapBuffers();
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("Transformation");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(Idle);
    glutMainLoop();

    return 0;
}


