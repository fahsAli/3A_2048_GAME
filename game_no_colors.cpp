#include "game.h"


game::Game::Game(){
    _score = 0;
    _move_num = 0;
    _grille_size = 0;
    srand(time(0));
}

int game::Game::score(){

    _score = 0;
    for(int i=0;i<_grille.capacity();i++){
        if(_grille.at(i)>1){
            _score += _grille.at(i);
        }
    }
    return _score;
}

int game::Game::move_num(){
    return _move_num;
}

std::string display_number(int num){

    std::string str;
    

    while(num>0){
        str = std::to_string(num%10)+str; 
        num = num / (10);
    }
    str = " " + str;
    str = str + " " + " " + " " + " ";

    if(str.length() > 6){
        str.resize(6);
    }
    return str;
}

void game::Game::display(){
    //std::system("clear");
    std::cout << "score : " << this->score() << std::endl;
    std::cout << "movement number : " << this->move_num() << std::endl;
    for(int i=0;i<_grille_size;i++){
        std::cout << "--------";
    }
    std::cout << "-" << std::endl;
    for(int i=0;i<_grille.capacity();i++){
        std::cout << "| " << ((_grille.at(i)>1)?display_number(_grille.at(i)):"      ");
        if(i%_grille_size == (_grille_size-1)){
            std::cout << "|" <<std::endl;
            for(int i=0;i<_grille_size;i++){
                std::cout << "--------";
            }
            std::cout << "-" << std::endl;
        }
    }   
}

bool game::Game::full_grille(){
    for(int i=0;i<_grille.capacity();i++){
        if(_grille.at(i)<2){
            return false;
        }
    }
    return true;
}

void game::Game::rand_generator(){
    int rand_value;
    int pos;
    if(!this->full_grille()){
        do {
            rand_value = (rand()%100);
            pos = rand_value%_grille.capacity();
        }while((_grille.at(pos)!=0));
    }
    _grille.at(pos) = ((rand_value<=20)?4:2);
    _score = this->score();
    _move_num++;
}



void game::Game::move(key k){

    bool change = false;
    bool global_change = false;
    int cpt = 0;
    //if(!this->full_grille()){
        if(k == key::up){
            for(int i=_grille_size;i<_grille.capacity();i++){
                if((_grille.at(i)==0)&&(_grille.at(i-_grille_size)==1)){
                    // rien
                }else if((_grille.at(i) == _grille.at(i-_grille_size))&&(_grille.at(i-_grille_size)!=0)){
                    _grille.at(i-_grille_size)+=_grille.at(i);
                    _grille.at(i)=1;
                    global_change = true;
                }else if((_grille.at(i) != _grille.at(i-_grille_size))&&(_grille.at(i-_grille_size)!=0)&&(_grille.at(i-_grille_size)!=1)){
                    // rien
                }else if(((_grille.at(i) != _grille.at(i-_grille_size))&&(_grille.at(i-_grille_size)==1))){
                    _grille.at(i-_grille_size)=_grille.at(i);
                    _grille.at(i)=0;
                    global_change = true;
                }else if(((_grille.at(i) != _grille.at(i-_grille_size))&&(_grille.at(i-_grille_size)==0))){
                    
                    for(int j=1;j<=(i/_grille_size);j++){
                        if(_grille.at(i-j*_grille_size)== 0){
                            // rien
                        }else if((_grille.at(i-j*_grille_size) != 0)&&(_grille.at(i-j*_grille_size) != 1)){

                            if(_grille.at(i-j*_grille_size) == _grille.at(i)){
                                _grille.at(i-(j)*_grille_size) += _grille.at(i);
                            }else {
                                _grille.at(i-(j-1)*_grille_size) = _grille.at(i);
                            }
                            change = true;
                            global_change = true;
                            _grille.at(i)=0;           
                            break;
                    
                        }else if(_grille.at(i-j*_grille_size) == 1){
                            _grille.at(i-j*_grille_size) = _grille.at(i);
                            _grille.at(i)=0;
                            change = true;
                            global_change = true;
                            break;
                        }
                        cpt = j;
                    } // for inter
                    
                    if((!change)&&(cpt != 0)){
                        _grille.at(i-(cpt)*_grille_size) = _grille.at(i);
                        _grille.at(i)=0;
                        global_change = true;
                    }
                    change = false;
                }

            }
                for(int i=0;i<_grille.capacity();i++){
                    if(_grille.at(i)==1){
                        _grille.at(i) = 0;
                    }
                }
        }else if(k == key::down){
            for(int i=(_grille.capacity()-_grille_size-1);i>=0;i--){
                if((_grille.at(i)==0)&&(_grille.at(i+_grille_size)==1)){
                    // rien
                }else if((_grille.at(i)==_grille.at(i+_grille_size))&&(_grille.at(i+_grille_size) != 0)){
                    _grille.at(i+_grille_size)+=_grille.at(i);
                    _grille.at(i)=1;
                    global_change = true;
                }else if((_grille.at(i) != _grille.at(i+_grille_size))&&(_grille.at(i+_grille_size)!=0)&&(_grille.at(i+_grille_size)!=1)){
                    // rien
                }else if(((_grille.at(i) != _grille.at(i+_grille_size))&&(_grille.at(i+_grille_size)==1))){
                    _grille.at(i+_grille_size)=_grille.at(i);
                    _grille.at(i)=0;
                    global_change = true;
                }else if((_grille.at(i) != _grille.at(i+_grille_size))&&(_grille.at(i+_grille_size)==0)){

                    for(int j=1;j<=(_grille_size-i/_grille_size-1);j++){
                        if(_grille.at(i+j*_grille_size)== 0){
                            // rien
                        }else if((_grille.at(i+j*_grille_size) != 0)&&(_grille.at(i+j*_grille_size) != 1)){

                            if(_grille.at(i+j*_grille_size) == _grille.at(i)){
                                _grille.at(i+(j)*_grille_size) += _grille.at(i);
                            }else {
                                _grille.at(i+(j-1)*_grille_size) = _grille.at(i);
                            }
                            change = true;
                            global_change = true;
                            _grille.at(i)=0;           
                            break;
                    
                        }else if(_grille.at(i+j*_grille_size) == 1){
                            _grille.at(i+j*_grille_size) = _grille.at(i);
                            _grille.at(i)=0;
                            change = true;
                            global_change = true;
                            break;
                        }
                        cpt = j;
                    }//for inter

                    if((!change)&&(cpt != 0)){
                        _grille.at(i+(cpt)*_grille_size) = _grille.at(i);
                        _grille.at(i)=0;
                        global_change = true;
                    }
                    change = false;
                }
            }
                for(int i=0;i<_grille.capacity();i++){
                    if(_grille.at(i)==1){
                        _grille.at(i) = 0;
                    }
                }
        }else if(k == key::left){
            for(int i=0;i<_grille.capacity();i++){
                if(i%_grille_size != 0){
                    if((_grille.at(i) == 0)&&(_grille.at(i-1)==1)){
                        // rien
                    }else if((_grille.at(i) == _grille.at(i-1))&&(_grille.at(i-1) != 0)){
                        _grille.at(i-1)+=_grille.at(i);
                        _grille.at(i)=1;
                        global_change = true;
                    }else if((_grille.at(i) != _grille.at(i-1))&&(_grille.at(i-1) != 0)&&(_grille.at(i-1) != 1)){
                        // rien
                    }else if((_grille.at(i) != _grille.at(i-1))&&(_grille.at(i-1) == 1)){
                        _grille.at(i-1)=_grille.at(i);
                        _grille.at(i)=0;
                        global_change = true;
                    }else if((_grille.at(i) != _grille.at(i-1))&&(_grille.at(i-1)==0)){

                        for(int j=1;j<=(i%_grille_size);j++){
                            if(_grille.at(i-1*j) == 0){
                                //rien
                            }else if((_grille.at(i-1*j) != 0)&&(_grille.at(i-1*j) != 1)){

                                if(_grille.at(i-1*j) == _grille.at(i)){
                                    _grille.at(i-1*j) += _grille.at(i);
                                }else {
                                    _grille.at(i-1*(j-1)) = _grille.at(i);
                                }
                                change = true;
                                global_change = true;
                                _grille.at(i)=0;           
                                break;

                            }else if(_grille.at(i-1*j) == 1){
                                _grille.at(i-1*j) = _grille.at(i);
                                _grille.at(i)=0;
                                change = true;
                                global_change = true;
                                break;
                            }
                            cpt = j;
                        }//for inter 

                        if((!change)&&(cpt != 0)){
                            _grille.at(i-1*cpt) = _grille.at(i);
                            _grille.at(i)=0;
                            global_change = true;
                        }
                        change = false;
                    }
                }
            }
                for(int i=0;i<_grille.capacity();i++){
                    if(_grille.at(i)==1){
                        _grille.at(i) = 0;
                    }
                }
        }else if(k == key::right){
            for(int i=(_grille.capacity()-1);i>=0;i--){
                if(i%_grille_size != (_grille_size-1)){
                    if((_grille.at(i) == 0)&&(_grille.at(i+1)==1)){
                        // rien
                    }else if((_grille.at(i) == _grille.at(i+1))&&(_grille.at(i+1) != 0)){
                        _grille.at(i+1)+=_grille.at(i);
                        _grille.at(i)=1;
                        global_change = true;
                    }else if((_grille.at(i) != _grille.at(i+1))&&(_grille.at(i+1) != 0)&&(_grille.at(i+1) != 1)){
                        // rien
                    }else if((_grille.at(i) != _grille.at(i+1))&&(_grille.at(i+1) == 1)){
                        _grille.at(i+1)=_grille.at(i);
                        _grille.at(i)=0;
                        global_change = true;
                    }else if((_grille.at(i) != _grille.at(i+1))&&(_grille.at(i+1)==0)){

                        for(int j=1;j<=(_grille_size-(i%_grille_size+1));j++){
                            if(_grille.at(i+1*j) == 0){
                                //rien
                            }else if((_grille.at(i+1*j) != 0)&&(_grille.at(i+1*j) != 1)){

                                if(_grille.at(i+1*j) == _grille.at(i)){
                                    _grille.at(i+1*j) += _grille.at(i);
                                }else {
                                    _grille.at(i+1*(j-1)) = _grille.at(i);
                                }
                                change = true;
                                global_change = true;
                                _grille.at(i)=0;           
                                break;

                            }else if(_grille.at(i+1*j) == 1){
                                _grille.at(i+1*j) = _grille.at(i);
                                _grille.at(i)=0;
                                change = true;
                                global_change = true;
                                break;
                            }
                            cpt = j;
                        }//for inter 

                        if((!change)&&(cpt != 0)){
                            _grille.at(i+1*cpt) = _grille.at(i);
                            _grille.at(i)=0;
                            global_change = true;
                        }
                        change = false;
                    }
                }
            }

                for(int i=0;i<_grille.capacity();i++){
                    if(_grille.at(i)==1){
                        _grille.at(i) = 0;
                    }
                }

        }//fi

        if(global_change){
            this->rand_generator();
        }
    //}
}

bool game::Game::can_move(){

    for(int i=0;i<_grille.capacity();i++){
        if(_grille.at(i)==2048){
            std::cout << "\n ---------------- victory ----------------" << std::endl;
            return false;
        }
    }

    //if(k == key::up){
        for(int i=(_grille_size);i<_grille.capacity();i++){
            if(i>(_grille_size-1)){
                for(int j=1;j<=(i/_grille_size);j++){
                    if((_grille.at(i)==_grille.at(i-j*_grille_size))&&(_grille.at(i-j*_grille_size)!=0)){
                        return true;
                    }else if((_grille.at(i)!=_grille.at(i-j*_grille_size))&&(_grille.at(i-j*_grille_size)!=0)){
                        break;
                    }else{
                        return true;
                        //_grille.at(i-j*_grille_size)== 0 donc : rien
                    }
                }
            }
        }
    //}else if(k == key::down){
        for(int i=(_grille.capacity()-_grille_size-1);i>=0;i--){
            if(i<=(_grille.capacity()-_grille_size-1)){
                for(int j=1;j<=(_grille_size-i/_grille_size-1);j++){
                    if((_grille.at(i)==_grille.at(i+j*_grille_size))&&(_grille.at(i+j*_grille_size)!=0)){
                        return true;
                    }else if((_grille.at(i)!=_grille.at(i+j*_grille_size))&&(_grille.at(i+j*_grille_size)!=0)){
                        break;
                    }else{
                        return true;
                        //_grille.at(i+j*_grille_size)== 0 donc : rien
                    }
                }
            }
        }
    //}else if(k == key::left){
        for(int i=0;i<_grille.capacity();i++){
            if(i%_grille_size != 0){
                for(int j=1;j<=(i%_grille_size);j++){
                    if((_grille.at(i)==_grille.at(i-1*j))&&(_grille.at(i-1*j)!=0)){
                        return true;
                    }else if((_grille.at(i)!=_grille.at(i-1*j))&&(_grille.at(i-1*j)!=0)){
                        break;
                    }else{
                        return true;
                        //_grille.at(i-1*j) == 0 : rien
                    }
                }
            }
        }
    //}else if(k == key::right){
        for(int i=(_grille.capacity()-1);i>=0;i--){
            if(i%_grille_size != (_grille_size-1)){
                for(int j=1;j<=(_grille_size-(i%_grille_size+1));j++){
                    if((_grille.at(i)==_grille.at(i+1*j))&&(_grille.at(i+1*j)!=0)){
                        return true;
                    }else if((_grille.at(i)!=_grille.at(i+1*j))&&(_grille.at(i+1*j)!=0)){
                        break;
                    }else{
                        return true;
                        //_grille.at(i+1*j) == 0 : rien
                    }
                }
            }
        }
    //}

    std::cout << "\n ---------------- lost ----------------" << std::endl;
    return false;
}


void _2048(){

    std::cout << "  ########    ########    #      #    ########" << std::endl;
    std::cout << "         #    #      #    #      #    #      #" << std::endl;
    std::cout << "  ########    #      #    ########     ###### " << std::endl;
    std::cout << "  #           #      #           #    #      #" << std::endl;
    std::cout << "  ########    ########           #    ########" << std::endl;
    std::cout << ">>>>>>>>>>>>>>>>>> by Ali Fahs <<<<<<<<<<<<<<<<<" << std::endl;
}


void game::Game::play(){

    char k;
    bool quit=false;

    _2048();
    std::cout << "\n" << std::endl;

    std::cout << "choose the size : ";
    std::cin >> _grille_size;
    _grille.resize(_grille_size*_grille_size);
    for(int i=0;i<_grille.capacity();i++){
        _grille.at(i)=0;
    }
    int rand_value1 = (rand()%100);
    _grille.at(rand_value1%_grille.capacity()) = ((rand_value1<=20)?4:2);
    int rand_value2 = (rand()%100);
    while((rand_value1%_grille.capacity()) == (rand_value2%_grille.capacity())){
        rand_value2 = (rand()%100);
    }
    _grille.at(rand_value2%_grille.capacity()) = ((rand_value2<=20)?4:2);
    
    std::cout<<"| up : u | down : d | left : l | right : r | quit : q |" << std::endl;
    this->display();

    do{
        std::cout << "choose a key : ";
        std::cin >> k;
        std::cout << std::endl;

        switch (k)
        {
        case 'u': case 'U':
            this->move(key::up);
            break;
        case 'd': case 'D':
            this->move(key::down);
            break;
        case 'l': case 'L':
            this->move(key::left);
            break;
        case 'r': case 'R':
            this->move(key::right);
            break;
        case 'q': case 'Q':
            quit = true;
            break;
        default:
            std::cout << "undefined key try again ..."<<std::endl;
            break;
        }

        if(!quit){
        this->display();
        }  
    
    }while(can_move() && (!quit));

}