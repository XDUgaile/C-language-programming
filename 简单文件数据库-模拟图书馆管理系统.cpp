#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

// 借阅信息
struct Info {
	string borrower;	// 借阅者用户名
	int book_id;		// 图书id
	bool operator < (const Info &I) const {
		return borrower == I.borrower ? book_id < I.book_id : borrower < I.borrower;
	}
};

// 重载借阅信息输出输入操作
istream& operator >> (istream &in, Info &I) {
	in >> I.borrower >> I.book_id;
	return in;
}
ostream& operator << (ostream &out, Info &I) {
	out << I.borrower << "		" << I.book_id;
	return out;
}

// 借阅信息
multiset<Info> infos;

/**************************************
/ 从借阅信息中找某书的借阅者
/ para book_id: 书的id
/ return 借阅者用户名列表
**************************************/
vector<string> findBorrowersByBookId(int book_id) {
	vector<string> borrowers;
	for (auto info : infos)
		if (info.book_id == book_id)
			borrowers.push_back(info.borrower);
	return borrowers;
}

// 图书
class Book {
public:
  	int id;				// 图书编号, 为0表示被删除
	string name;		// 图书名称
	int amount, stock;	// 总量和剩余量
	Book(){}
	Book(int id, string name, int amount, int stock):
		id(id),name(name),amount(amount),stock(stock) {}

	/**************************************
	/ 借书
	/ para borrower: 借阅者用户名
	/ return: 是否借阅成功
	**************************************/
	bool borrow(string borrower) {
		if (!stock)
			return false;
		stock--;
		infos.insert({borrower, id});
		return true;
	}

	/**************************************
	/ 还书
	/ para borrower: 借阅者用户名
	/ return: 是否还书成功
	**************************************/
	bool returnBook(string borrower) {
		if (stock >= amount)
			return false;
		stock++;
		multiset<Info>::iterator it = infos.find({borrower, id});
		if (it == infos.end())
			return false;
		infos.erase(it);
		return true;
	}

	/**************************************
	/ 删除该书
	**************************************/
	void clear() {
		id = amount = stock = 0, name = "";
	}

	// 重载 < 排序用
	bool operator < (const Book &b) const {
		return id < b.id;
	}
};

// 重载图书输入输出
ostream& operator << (ostream &out, Book &B) {
    out << B.id << "		" << B.name << "		" << B.amount << "		" << B.stock;
    return out;
}
istream& operator >> (istream &in, Book &B) {
	in >> B.id >> B.name >> B.amount >> B.stock;
	return in;
}

// 图书
vector<Book> books;

/**************************************
/ 根据书名查找图书
/ para name: 书名
/ return: 该书的地址, 没有则返回NULL
**************************************/
Book* findBookByName(string name) {
	for (int i = 0; i < (int)books.size(); i++)
		if (books[i].id && books[i].name == name)
			return &books[i];
	return NULL;
}

/**************************************
/ 根据图书编号查找图书
/ para id: 图书编号
/ return: 该书的地址, 没有则返回NULL
**************************************/
Book* findBookById(int id) {
	for (int i = 0; i < (int)books.size(); i++)
		if (books[i].id && books[i].id == id)
			return &books[i];
	return NULL;
}

// 用户类
class User {
protected:
	string user_name;	// 用户名

	/**************************************
	/ 列出所有图书信息
	**************************************/
	void listAllBooks() {
		printBooksInfoTitle();
		int cnt = 1;
		for (auto book : books)
			if (book.id)
				cout << cnt++ << "		" << book << endl;
	}

	/**************************************
	/ 根据图书名称搜索图书信息
	/ para name: 图书名称
	**************************************/
	void searchBooksByName(string name) {
		Book *book = findBookByName(name);
		if (book != NULL) {
			printBooksInfoTitle();
			cout << "1		" << *book << endl;
		}
		else
			cout << "No such book in this library!" << endl;
	}

	/**************************************
	/ 根据图书id搜索图书信息
	/ para id: 图书编号
	**************************************/
	void searchBooksById(int id) {
		Book *book = findBookById(id);
		if (book != NULL) {
			printBooksInfoTitle();
			cout << "1		" << *book << endl;
		}
		else
			cout << "No such book in this library!" << endl;
	}

	/**************************************
	/ 查询图书的借阅者
	/ para *book: 查询的图书的指针
	**************************************/
	void searchBorrowers(Book *book) {
		if (book == NULL)
			cout << "Search Error: No such book in this library!" << endl;
		else {
			cout << "Borrower(s) of Book " << book->id << " " << book->name << ":" << endl;
			vector<string> borrowers = findBorrowersByBookId(book->id);
			for (auto borrower : borrowers)
				cout << borrower << endl;
		}
	}

	/**************************************
	/ 打印第一栏信息
	**************************************/
	void printBooksInfoTitle() {
		cout << "No.		" << "ID		" << "Name		" << "Amount		" << "Stock		" << endl;
	}

public:
	const static int OPERATION_EXIT = 0;
	const static int OPERATION_LIST = 1;
	const static int OPERATION_SEARCH_BY_NAME = 2;
	const static int OPERATION_SEARCH_BY_ID = 3;
	const static int OPERATION_SEARCH_BORROWER_BY_NAME = 4;
	const static int OPERATION_SEARCH_BORROWER_BY_ID = 5;

	/**************************************
	/ 显示命令面板
	**************************************/
	virtual void showCommand(){
  		cout << "--------Library System--------" << endl;
  		cout << "0. Exit" << endl;
  		cout << "1. List all books in library" << endl;
  		cout << "2. Search books by book name" << endl;
  		cout << "3. Search books by book id" << endl;
  		cout << "4. Search borrowers by book name" << endl;
  		cout << "5. Search borrowers by book id" << endl;
	}
	/**************************************
	/ 处理命令操作
	/ para op: 操作序号
	/ return: 退出系统 false, 否则 true
	**************************************/
	virtual bool operate(int op) {
		if (op == OPERATION_EXIT)
			return false;
		else if (op == OPERATION_LIST)
			listAllBooks();
		else if (op == OPERATION_SEARCH_BY_NAME) {
			cout << "Book Name: ";
			string book_name;
			cin >> book_name;
			searchBooksByName(book_name);
		}
		else if (op == OPERATION_SEARCH_BY_ID) {
			cout << "Book ID: ";
			int book_id;
			cin >> book_id;
			searchBooksById(book_id);
		}
		else if (op == OPERATION_SEARCH_BORROWER_BY_NAME) {
			cout << "Book Name: ";
			string book_name;
			cin >> book_name;
			Book *book = findBookByName(book_name);
			searchBorrowers(book);
		}
		else if (op == OPERATION_SEARCH_BORROWER_BY_ID) {
			cout << "Book ID: ";
			int book_id;
			cin >> book_id;
			Book *book = findBookById(book_id);
			searchBorrowers(book);
		}
		return true;
	}
	User(){}
	User(string user_name):user_name(user_name){}
};

// 读者用户
class Reader : public User {
private:
  	multiset<int> borrowedBooks;	// 借阅的图书编号

  	/**************************************
	/ 查询已借阅图书
	**************************************/
	void listBorrowedBooks() {
		cout << "User Name:" << user_name << endl;
		cout << "Borrowed books:" << endl;
		cout << "No.		"<< "ID		" << "Name		" << endl;
		int cnt = 1;
		for (auto book_id : borrowedBooks) {
			Book *book = findBookById(book_id);
			cout << cnt++ << "		" << book->id << "		" << book->name << endl;
		}
	}

	/**************************************
	/ 还书
	/ para no: 已借阅图书的序号
	/ return: 是否还书成功
	**************************************/
	bool returnBook(int no) {
		if (no <= 0 || no > (int)borrowedBooks.size())
			return false;
		int cnt = 1;
		for (multiset<int>::iterator it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it)
			if (no == cnt++) {
				Book* book = findBookById(*it);
				book->returnBook(user_name);
				borrowedBooks.erase(it);
				break;
			}
		return true;
	}

	/**************************************
	/ 输出借阅操作交互信息
	/ para flag: 借阅操作结果标识
	**************************************/
	void printBorrowLog(int flag) {
		if (flag == BORROW_FLAG_SUC)
			cout << "Borrowed successfully!" << endl;
		else if (flag == BORROW_FLAG_NO_REMAIN)
			cout << "Borrowed failed! All books have been borrowed!" << endl;
		else if (flag == BORROW_FLAG_NO_BOOK)
			cout << "Borrowed failed! No such book in this library!" << endl;
	}

	/**************************************
	/ 输出还书操作交互信息
	/ para flag: 还书操作结果标识
	**************************************/
	void printReturnLog(bool flag) {
		if (flag)
			cout << "Return successfully!" << endl;
		else
			cout << "Return Error: Please check your input!" << endl;
	}

public:
	const static int OPERATION_LIST_BORROWED = 6;
	const static int OPERATION_BORROW_BY_NAME = 7;
	const static int OPERATION_BORROW_BY_ID = 8;
	const static int OPERATION_RETURN = 9;
	const static int BORROW_FLAG_SUC = 1;
	const static int BORROW_FLAG_NO_BOOK = 2;
	const static int BORROW_FLAG_NO_REMAIN = 3;
	Reader(string user_name):User(user_name) {
		// 初始化, 找到借阅的图书
		borrowedBooks.clear();
		for (auto info : infos)
			if (info.borrower == user_name)
				borrowedBooks.insert(info.book_id);
	}

	/**************************************
	/ 显示命令面板
	**************************************/
  	virtual void showCommand() {
  		User::showCommand();
  		cout << "6. List borrowed books" << endl;
  		cout << "7. Borrow book by book name" << endl;
  		cout << "8. Borrow book by book id" << endl;
  		cout << "9. Return book" << endl;
  	}

	/**************************************
	/ 处理命令操作
	/ para op: 操作序号
	/ return: 退出系统 false, 否则 true
	**************************************/
  	virtual bool operate(int op) {
  		if (!User::operate(op))
  			return false;
  		if (op == OPERATION_LIST_BORROWED)
  			listBorrowedBooks();
  		else if (op == OPERATION_BORROW_BY_NAME) {
  			cout << "Book Name: ";
			string book_name;
			cin >> book_name;
			Book *book = findBookByName(book_name);
  			printBorrowLog(borrowBook(book));
  		}
  		else if (op == OPERATION_BORROW_BY_ID) {
			cout << "Book ID: ";
			int book_id;
			cin >> book_id;
			Book *book = findBookById(book_id);
  			printBorrowLog(borrowBook(book));
  		}
  		else if (op == OPERATION_RETURN) {
  			listBorrowedBooks();
  			cout << "Please choose the number of borrowed book to return: ";
  			int no;
  			cin >> no;
  			printReturnLog(returnBook(no));
  		}
  		return true;
  	}

	/**************************************
	/ 借书
	/ para *book: 借阅书籍指针
	/ return: 借书操作结果标识
	**************************************/
	int borrowBook(Book *book) {
		if (book == NULL)
			return BORROW_FLAG_NO_BOOK;
		if (book->borrow(user_name)) {
			borrowedBooks.insert(book->id);
			return BORROW_FLAG_SUC;
		}
		return BORROW_FLAG_NO_REMAIN;
	}
};

// 管理员用户
class Admin : public User {
private:
	/**************************************
	/ 添加图书
	/ para id: 图书编号
	/ para name: 书名
	/ para amount: 数量
	/ return: 添加图书操作结果标识
	**************************************/
	int addBook(int id, string name, int amount) {
		if (findBookById(id) != NULL)
			return ADD_BOOK_FLAG_ID_NOT_UNIQUE;
		if (amount <= 0)
			return ADD_BOOK_FLAG_AMOUNT_NOT_POSTIVE;
		books.emplace_back(id, name, amount, amount);
		return ADD_BOOK_FLAG_SUC;
	}

	/**************************************
	/ 删除图书
	/ para id: 图书编号
	/ return: 删除图书操作结果标识
	**************************************/
	int deleteBook(int book_id) {
		Book *book = findBookById(book_id);
		if (book == NULL)
			return DELETE_BOOK_FLAG_NO_BOOK;
		if (book->amount > book->stock)
			return DELETE_BOOK_FLAG_ON_LOAN;
		book->clear();
		return DELETE_BOOK_FLAG_SUC;
	}

	/**************************************
	/ 编辑图书
	/ para id: 图书编号
	/ return: 编辑图书操作结果标识
	**************************************/
	int editBook(int book_id) {
		Book *book = findBookById(book_id);
		if (book == NULL)
			return EDIT_BOOK_FLAG_NO_BOOK;
		printBooksInfoTitle();
		cout << "1		" << *book << endl;
		cout << "Name		" << "Amount" << endl;
		string new_name;
		int new_amount;
		cin >> new_name >> new_amount;
		int delta = new_amount - book->amount;
		if (book->stock + delta <= 0)
			return EDIT_BOOK_FLAG_NO_STOCK;
		book->name = new_name;
		book->stock += delta;
		book->amount = new_amount;
		return EDIT_BOOK_FLAG_SUC;
	}

	/**************************************
	/ 查询所有借阅信息
	**************************************/
	void listBorrowing() {
		cout << "No.		borrower(s)	Book id 	Book name" << endl;
		int cnt = 1;
		for (auto info : infos) {
			string book_name = findBookById(info.book_id)->name;
			cout << cnt++ << "		" << info << "		" << book_name << endl;
		}
	}

	/**************************************
	/ 添加借阅信息
	/ para borrower_name: 借阅者用户名
	/ para amount: 图书编号
	/ return: 添加借阅信息操作结果标识
	**************************************/
	int addBorrowing(string borrower_name, int book_id) {
		Reader borrower(borrower_name);
		return borrower.borrowBook(findBookById(book_id));
	}

	/**************************************
	/ 删除借阅信息
	/ para no: 借阅信息的序号
	/ return: 删除借阅信息操作结果标识
	**************************************/
	bool deleteBorrowing(int no) {
		if (no <= 0 ||  no > (int)infos.size())
			return false;
		int cnt = 1;
		for (auto info : infos)
			if (no == cnt++) {
				Book *book = findBookById(info.book_id);
				book->returnBook(info.borrower);
				break;
			}
		return true;
	}

	/**************************************
	/ 编辑借阅信息
	/ para no: 借阅信息的序号
	/ return: 编辑借阅信息操作结果标识
	**************************************/
	int editBorrowing(int no) {
		if (no <= 0 ||  no > (int)infos.size())
			return EDIT_BORROWING_FLAG_INVALID_INPUT;
		int cnt = 1;
		cout << "Borrower	Book ID" << endl;
		string borrower;
		int book_id;
		cin >> borrower >> book_id;
		for (auto info : infos)
			if (no == cnt++) {
				deleteBorrowing(no);
				return addBorrowing(borrower, book_id);
			}
		return -1;
	}

	/**************************************
	/ 输出添加图书操作交互信息
	/ para flag: 添加图书操作结果标识
	**************************************/
	void printAddBookLog(int flag) {
		if (flag == ADD_BOOK_FLAG_SUC)
			cout << "Added successfully!" << endl;
		else if (flag == ADD_BOOK_FLAG_ID_NOT_UNIQUE)
			cout << "Add Error: Book ID is not unique!" << endl;
		else if (flag == ADD_BOOK_FLAG_AMOUNT_NOT_POSTIVE)
			cout << "Add Error: The amount is invalid!" << endl;
	}

	/**************************************
	/ 输出删除图书操作交互信息
	/ para flag: 删除图书操作结果标识
	**************************************/
	void printDeleteBookLog(int flag) {
		if (flag == DELETE_BOOK_FLAG_SUC)
			cout << "Deleted successfully!" << endl;
		else if (flag == DELETE_BOOK_FLAG_NO_BOOK)
			cout << "Delete Error: No such book in this library!" << endl;
		else if (flag == DELETE_BOOK_FLAG_ON_LOAN)
			cout << "Deleted Error: Book is on loan!" << endl;
	}

	/**************************************
	/ 输出编辑图书操作交互信息
	/ para flag: 编辑图书操作结果标识
	**************************************/
	void printEditBookLog(int flag) {
		if (flag == EDIT_BOOK_FLAG_SUC)
			cout << "Edited successfully!" << endl;
		else if (flag == EDIT_BOOK_FLAG_NO_BOOK)
			cout << "Edit Error: No such book in this library!" << endl;
		else if (flag == EDIT_BOOK_FLAG_NO_STOCK)
			cout << "Edit Error: No stocked book!" << endl;
	}

	/**************************************
	/ 输出添加借阅信息操作交互信息
	/ para flag: 添加借阅信息操作结果标识
	**************************************/
	void printAddBorrowingLog(int flag) {
		if (flag == Reader::BORROW_FLAG_SUC)
			cout << "Added successfully!" << endl;
		else if (flag == Reader::BORROW_FLAG_NO_BOOK)
			cout << "Add Error: No such book in this library!" << endl;
		else if (flag == Reader::BORROW_FLAG_NO_REMAIN)
			cout << "Add Error: All books have been borrowed!" << endl;
	}

	/**************************************
	/ 输出删除借阅信息操作交互信息
	/ para flag: 删除借阅信息操作结果标识
	**************************************/
	void printDeleteBorrowingLog(bool flag) {
		if (flag)
			cout << "Deleted successfully!" << endl;
		else
			cout << "Delete Error: Please check your input!" << endl;
	}

	/**************************************
	/ 输出编辑借阅信息操作交互信息
	/ para flag: 编辑借阅信息操作结果标识
	**************************************/
	void printEditBorrowing(int flag) {
		if (flag == EDIT_BORROWING_FLAG_INVALID_INPUT)
			cout << "Edit Error: Please check your input!" << endl;
		else if (flag == Reader::BORROW_FLAG_SUC)
			cout << "Edited successfully!" << endl;
		else if (flag == Reader::BORROW_FLAG_NO_BOOK)
			cout << "Edit Error: No such book in this library!" << endl;
		else if (flag == Reader::BORROW_FLAG_NO_REMAIN)
			cout << "Edit Error: All books have been borrowed!" << endl;
	}

public:
	const static int OPERATION_ADD_BOOK = 6;
	const static int OPERATION_EDIT_BOOK = 7;
	const static int OPERATION_DELETE_BOOK = 8;
	const static int OPERATION_LIST_BORROWING = 9;
	const static int OPERATION_ADD_BORROWING = 10;
	const static int OPERATION_EDIT_BORROWING = 11;
	const static int OPERATION_DELETE_BORROWING = 12;
	const static int ADD_BOOK_FLAG_SUC = 1;
	const static int ADD_BOOK_FLAG_ID_NOT_UNIQUE = 2;
	const static int ADD_BOOK_FLAG_AMOUNT_NOT_POSTIVE = 3;
	const static int DELETE_BOOK_FLAG_SUC = 1;
	const static int DELETE_BOOK_FLAG_NO_BOOK = 2;
	const static int DELETE_BOOK_FLAG_ON_LOAN = 3;
	const static int EDIT_BOOK_FLAG_SUC = 1;
	const static int EDIT_BOOK_FLAG_NO_BOOK = 2;
	const static int EDIT_BOOK_FLAG_NO_STOCK = 3;
	const static int EDIT_BORROWING_FLAG_INVALID_INPUT = 0;
	const static int EDIT_BORROWING_FLAG_SUC = 1;

	/**************************************
	/ 显示命令面板
	**************************************/
	virtual void showCommand() {
		User::showCommand();
		cout << "6. Add book" << endl;
		cout << "7. Edit book" << endl;
		cout << "8. Delete book" << endl;
		cout << "9. List borrowing information" << endl;
		cout << "10. Add borrowing information" << endl;
		cout << "11. Edit borrowing information" << endl;
		cout << "12. Delete borrowing information" << endl;
	}

	/**************************************
	/ 处理命令操作
	/ para op: 操作序号
	/ return: 退出系统 false, 否则 true
	**************************************/
	virtual bool operate(int op) {
		if (!User::operate(op))
			return false;
		if (op == OPERATION_ADD_BOOK) {
			cout << "ID		" << "Name		" << "Amount" << endl;
			int id, amount;
			string name;
			cin >> id >> name >> amount;
			printAddBookLog(addBook(id, name, amount));
		}
		else if (op == OPERATION_DELETE_BOOK) {
			cout << "Book ID: ";
			int id;
			cin >> id;
			printDeleteBookLog(deleteBook(id));
		}
		else if (op == OPERATION_EDIT_BOOK) {
			cout << "Book ID: ";
			int id;
			cin >> id;
			printEditBookLog(editBook(id));
		}
		else if (op == OPERATION_LIST_BORROWING)
			listBorrowing();
		else if (op == OPERATION_ADD_BORROWING) {
			cout << "Borrower	Book ID" << endl;
			string borrower;
			int book_id;
			cin >> borrower >> book_id;
			printAddBorrowingLog(addBorrowing(borrower, book_id));
		}
		else if (op == OPERATION_DELETE_BORROWING) {
			listBorrowing();
			cout << "Please choose the number of borrowing information to delete: ";
			int no;
			cin >> no;
			printDeleteBorrowingLog(deleteBorrowing(no));
		}
		else if (op == OPERATION_EDIT_BORROWING) {
			listBorrowing();
			cout << "Please choose the number of borrowing information to edit: ";
			int no;
			cin >> no;
			printEditBorrowing(editBorrowing(no));
		}
		return true;
	}
	Admin(string user_name):User(user_name) {}
};

/**************************************
/ 加载图书信息
/ para file_name: 存放图书信息的文件名
**************************************/
void loadBooks(string file_name) {
	ifstream f(file_name, ios::in);
	Book book;
	while (f >> book)
		books.push_back(book);
	sort(books.begin(), books.end());
	f.close();
}

/**************************************
/ 加载借阅信息
/ para file_name: 存放借阅信息的文件名
**************************************/
void loadInfo(string file_name) {
	ifstream f(file_name, ios::in);
	Info info;
	while (f >> info)
		infos.insert(info);
	f.close();
}

/**************************************
/ 加载数据信息
/ para book_file_name: 存放图书信息的文件名
/ para info_file_name: 存放借阅信息的文件名
**************************************/
void loadLibrary(string book_file_name, string info_file_name) {
	loadBooks(book_file_name);
	loadInfo(info_file_name);
}

/**************************************
/ 保存图书信息
/ para file_name: 存放图书信息的文件名
**************************************/
void updateBooks() {
	ofstream f("books.txt", ios::out);
	for (auto book : books)
		if (book.id)
			f << book << endl;
	f.close();
}

/**************************************
/ 保存借阅信息
/ para file_name: 存放借阅信息的文件名
**************************************/
void updateInfo() {
	ofstream f("info.txt", ios::out);
	for (auto info : infos)
		f << info << endl;
	f.close();
}

/**************************************
/ 保存数据信息
/ para book_file_name: 存放图书信息的文件名
/ para info_file_name: 存放借阅信息的文件名
**************************************/
void updateLibrary(string book_file_name, string info_file_name) {
	updateBooks();
	updateInfo();
}

int main(int argc, char const *argv[]) {
	const string book_data_file_name = "books.txt";
	const string info_data_file_name = "info.txt";
	// 进入系统, 加载信息
	loadLibrary(book_data_file_name, info_data_file_name);
	string identity = argv[1];
	string user_name = argv[2];
	User *user;		// 多态
	if (identity == "-u")
		user = new Reader(user_name);
	else if (identity == "-a")
		user = new Admin(user_name);
	else {
		cout << "ERROR: Unknown operation: \"" << identity << "\"" << endl;
		exit(EXIT_FAILURE);
	}
	while (1) {
		user->showCommand();
		int op;
		cin >> op;
		if (!user->operate(op))
			break;
	}
	// 退出系统, 更新信息
	updateLibrary(book_data_file_name, info_data_file_name);
	return 0;
}
