# synomilia

# 개요
리눅스 프로그래밍 및 네트워크 프로그래밍을 이해하기위하여 시작하는 프로젝트이며 가장 기본적인 메신저 애플리케이션을 개발한다.
우리가 이루고자 하는 목표는 다음과 같다. 
1. 네트워크 프로그래밍에 대한 이해 
- TCP, UDP에 대한 이해
- 애플리케이션 레이어의 프로토콜에 대한 이해 
- C/S구조에 대한 이해 (Client/Server Structure)
2. 리눅스 프로그래밍에 대한 이해
- 리눅스 Socket에 대한 이해
- 리눅스 Thread에 대한 이해

Overview
We develop Messanger Application to understand the linux & network programming.
Our Goal is as follow : 
1. Understand for Network programming
- Understand the TCP & UDP
- Understand the our application protocol on Application Layer.
- Understand the Client / Server Structure
2. Understand for Linux Programming
- Understand Socket on Linux
- Understand Thread on Linux


# 요구 사항(Requirement)
1. CLI(Command Line Interface)환경에서 이용가능하도록 지원한다.
We support the environment on CLI(Command Line Interface)

2. 계정을 기반으로 하여 이용할 수 있게한다.
Our Application can use on the only account

3. 계정에서는 지인을 관리할 수 있도록 한다.
User can manages the friends

4. 개인 및 그룹으로 메시지를 보낼 수 있다.
User can sends message to the private or group

5. 메시지외 멀티미디어 및 바이너리 파일을 전송할 수 있다.
User also can sends multimedia or binary

# 요구사항에 따른 설명
1. CLI(Command Line Interface)환경에서 이용가능하도록 지원한다.
[We support the environment on CLI(Command Line Interface)]
    - CLI환경은 synomilia_cli를 통해 동작되며 다음과 같은 option을 이용하여 동작할 수 있다.
      1) -help : help는 해당 앱에 대한 설명 및 실행법을 간단하게 서술 
      2) -user : user는 접속하고자 하는 사용자의 계정 id
      3) -host : host는 메신저를 이용하기 위한 서버주소 (없으면 기본주소를 통해 접속)
      4) -port : port는 서버의 포트번호 (없으면 기본 포트를 통해 접속)

2. 계정을 기반으로 하여 이용할 수 있게한다.
Our Application can use on the only account
    - 사용자에게 계정을 생성할 수 있게한다. 사용자에게 필요한 정보는 다음과 같다.
      a. id
      b. password
      c. user name
      d. email
      e. tel number
    - 사용자는 id와 password를 입력하여 서버에서 등록된 계정인지 인증후 메신저를 이용할 수 있도록한다.
    
3. 계정에서는 지인을 관리할 수 있도록 한다.
User can manages the friends
    - 계정을 인증하고 접속한 사용자는 자신의 지인의 목록을 볼 수 있다. 
    - 사용자는 지인을 추가 또는 삭제할 수 있다.
       cli 환경에서는 별도의 명령 또는 메뉴를 입력하여 동작하게 한다.

4. 개인 및 그룹으로 메시지를 보낼 수 있다.
User can sends message to the private or group
    - CLI환경에서는 메뉴를 입력하여 메시지를 보낼 수 있도록한다.
    - 메시지 방이 생성이 되며 구성원은 상대의 아이디로 지정할 수 있다.

5. 메시지외 멀티미디어 및 바이너리 파일을 전송할 수 있다.
User also can sends multimedia or binary
    - CLI 환경에서는 텍스트를 제외한 파일들은 명령을 통해 다운로드 받을 수 있다.
      이때 파일은 고유 식별 코드가 존재하며 이를 통해 다운로드 받을 수 있다.
    - 파일의 경우 일정기간이 지나면 다운로드를 받을 수 없다.