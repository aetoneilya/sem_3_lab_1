int cryptoSecMode() {
    printLine();
    long int p = 919, g = 7;
    long int xA, yA, xB, yB, k, key, r, e, keyEnd;
    cout << "You are Alice, please enter your secret code: ";
    cin >> xA;
    while (xA <= 1 || xA > p - 1) {
        cout << "Secret code must be greater than 1 but smaller than " << p - 1 << endl << "Please, enter it again: ";
        cin >> xA;
    }
    yA = modCompare(g, xA, p);
    cout << "Your open code is " << yA << "\nYou are safe to share it with anyone!\n";
    //xA = 433;
    //xB = 899; // enter
    cout << "Press any button to become Bob...\n";
    _getch();
    cout << "You are Bob now, please enter your secret code: ";
    cin >> xB;
    while (xB <= 1 || xB > p - 1) {
        cout << "Secret code must be greater than 1 but smaller than " << p - 1 << endl << "Please, enter it again: ";
        cin >> xB;
    }
    yB = modCompare(g, xB, p);
    cout << "Your open code is " << yB << "\nYou are safe to share it with anyone!\n";
    cout << "Press any button to become Alice...\n";
    _getch();
    cout << "You are Alice again, please enter your secret number that is mutually simple with " << p - 1 << " to encode message: ";
    
    cin >> k;
    while (((p - 1) % k) == 0) {
        cout << "That number is not mutually simple with " << p - 1 << endl << "You can try 673\n"<<"Please, enter it again: ";
        cin >> k;
    }
    //k = 17;

    cout << "Enter the key (Number) that you want to send to Bob: ";
    cin >> key;

    //шифропара которую мы отправляем Бобу

    r = modCompare(g, k, p);
    e = key * modCompare(yB, k, p);
    cout << "Sending cipher pair " << r <<' '<< e << " to Bob\n" ;

    cout << "Press any button to become Bob...\n";
    _getch();
    //боб расшивровывает
    cout << "You are Bob now.\nYou recieved cipher pair " << r << ' ' << e << " from Alice\n";
    cout << "Lets decode it\n";
    for (int i = 0; i < 20; i++) {
        cout << "|";//красивая загрузка
        Sleep(70);
    }
    cout <<"\nMessage decoded" <<endl;
    keyEnd = (e*modCompare(r,p-1-xB,p))%p;
    cout << "Message from Alice = "<< keyEnd << endl;
    return 0;
}

int extEucAlg(int a, int b, int& x, int& y) {
    int q, r, x1, x2, y1, y2, nod;
    //r1 = r1 * 1 + r2 * 0
    //r2 = r1 * 0 + r2 * 0
    x2 = 1, x1 = 0, y2 = 0, y1 = 1;
    while (b > 0) {
        q = a / b;
        r = a - q * b;
        x = x2 - q * x1;
        y = y2 - q * y1;
        a = b;
        b = r;
        x2 = x1;
        x1 = x;
        y2 = y1;
        y1 = y;
    }
    nod = a, x = x2, y = y2;
    return fabs(nod);
}