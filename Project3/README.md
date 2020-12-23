# Project 3
**본 프로젝트에서는 기존 프로젝트의 등록 리스트에 B-tree 자료구조를 사용하는 다단계 인덱스 (Multilevel Index)를 추가한다.**

## 구현된 프로그램

### 1)데이터 파일 레코드에 접근
접근하고자 하는 key 를 입력 받고 이 키를 B-tree 의 Search 메소드에 인자로 넘겨 주면, 그 메소드는 반환 값으로 넘어온 인자 key 에 해당하는 레코드의 데이터파일 시작 주소가 넘어온다. 이 주소값을 토대로 PurchaseFile.Read(destination_p, recAddr)와 같이 File 의 Read 함수를 호출하면 그 주소부터 시작되는 레코드가 destination_p 에 저장된다. 위와 같은 방식으로 데이터파일에 접근한다.
 
### 2)검색
검색 과정은 main.cpp 의 line503~536 에 구현하였다. 
사용자에게서 key 를 int 형으로 입력 받고 입력받은 key 값에 해당하는 아스키값을 갖는 character 로 변경시킨뒤 이를 활용하여 BTree 의 Search 메소드를 호출하여 검색을 수행한다. 즉 위에 언급한 방식과 같은 형식으로 수행된다.

### 3)삽입
삽입 과정은 purchase.cpp 의 insertPurchase() 메소드에 구현하였다. (line 403~468) 기존의 프로젝트에서와 동일하게 purchaseID 를 입력 받고 존재하지 않는 id 인 경우에만 삽입을 수행한다. 
존재하지 않는 경우 Game ID, memberID, purchaseDate 를 순서대로 입력 받고 key 의 경우엔 기존에 존재하던 인덱스의 다음 번호를 넣어준다. 이때 key 는 1부터 127 사이의 값을 벗어나서는 안된다.
그런 뒤 File Write 함수를 통해 fileOfPurchase.dat 파일의 내용을 수정해 주고 반환 값으로 받은 레코드의 주소 값을 활용하여 BTree 의 Insert 메소드를 호출하여 key 의 값과 레코드 주소를 저장해준다.

### 4)삭제
삭제 과정은 main.cpp 의 deleteByKey() 메소드에 구현하였다. (line 171~230)
삭제를 원하는 레코드의 key 를 입력 받아 BTree 의 Search 메소드를 호출하여 그 key 를 가진 레코드가 존재하는지 확인한다. 
존재하지 않는 경우 그대로 실행을 마치고 존재하는 경우엔 삭제를 수행한다. 
fileOfPurchase.dat 에서 입력 받은 key 와 같은 key를 갖는 레코드를 찾아 삭제해준다. 그런 뒤 수정된 주소 값들로 갱신해 주어야 하므로 BTree 도 알맞게 갱신시켜준다.

### 5)수정
수정 과정은 main.cpp 의 line 668~783 에 구현하였다. 
수정을 원하는 레코드의 key 를 입력 받아 BTree 의 Search 메소드를 호출하여 그 key 를 가진 레코드가 존재하는지 확인한다. 
존재하지 않는 경우 그대로 실행을 마치고 존재하는 경우엔 수정을 수행한다. Game ID, memberID, purchaseDate 를 순서대로 입력 받고 그에 따라 purchase 레코드를 수정해준다. 
그런 뒤 File Write 함수를 통해 fileOfPurchase.dat 파일의 내용을 수정해 주고 반환 값으로 받은 레코드의 주소 값을 활용하여 BTree class 의 Remove 와 Insert 메소드를 차례로 호출하여 그 키 값의 레코드 주소를 수정해 준다.

