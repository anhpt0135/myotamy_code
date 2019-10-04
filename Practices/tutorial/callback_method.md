###IDEA OF CREATE A FUNCTION CALLBACK
In main fucntion:

	
	DBinfor camtable;

	callback_register(func_callback); // duoc dinh nghia o tang hw

	//ham func_callback se lay thong tin tu hw va truyen vao bien global camtable;
	void func_callback(DBinfor db_infor){
		camtable.battery_level = db_infor.battery_level;
		camtable.battery_temp  = db_infor.battery_temp;
	}


	int main(){
		register_callback_func(callback_register);
		//sau khi goi ham register callback ta co the su dung bien global

		printf("%d", camtable.battery_level);
		printf("%d", camtable.battery_temp);
	}


	// o tang hw thi ham callback_register duoc dinh nghia de goi ham callback
	void callback_register(CAM_CALLBACK_FUNC func){
		DBinfor hwbattery;
		hwbattery.battery_level = func_get_battery_level();
		hwbattery.battery_temp = func_get_battery_temp();
		func(hwbattery);

		==> trong linux co the su dung ham 
		ret = pthread_create(&battery_thread, &battery_attr, run_check_battery, battery_cb);
		luc nay ham callback se la battery_cb nhu la mot arg duoc truyen vao ham run_check_battery

	}


	/*void *run_check_battery(void *arg){
		DBinfor hwbattery;
		hwbattery.battery_level = func_get_battery_level();
		hwbattery.battery_temp = func_get_battery_temp();
		CAM_CALLBACK_FUNC func = (CAM_CALLBACK_FUNC)arg;
		func(hwbattery);

	}
	*/


	===> Tu y tuong do ta lam nguoc lai bang cach truyen thong tin tu ham main de thuoc hien thong tin do trong tang hw

