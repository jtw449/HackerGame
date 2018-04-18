// Files will be manipulated by the player
class File {
	private:
		string name;
		string data;
		time_t access_time;
		time_t modify_time;
		time_t change_time;
		list <perm> permissions;
		user owner;

	public:
		// constructor
		File(string file_name, string data, list <perm> perm_flags, user file_owner) {
			this->name = file_name;
			this->data = data;
			this->access_time = time(nullptr);
			this->modify_time = this->access_time;
			this->change_time = this->access_time;
			this->permissions = perm_flags;
			this->owner = file_owner;
		}

		bool set_name(string file_name) {
			this->name = file_name;
			this->change_time = time(nullptr);
			return true;
		}

		bool write_data(string data) {
			this->data = data;
			this->modify_time = time(nullptr);
			this->access_time = this->modify_time;
			this->change_time = this->modify_time;
			return true;
		}

		bool append_data(string data) {
			this->data = this->data.append(data);
			this->modify_time = time(nullptr);
			this->access_time = this->modify_time;
			this->change_time = this->modify_time;
			return true;
		}

		bool change_ownership(user new_owner) {
			this->owner = new_owner;
			this->change_time = time(nullptr);
			return true;
		}

		bool change_permissions(list <perm> perm_flags) {
			this->permissions = perm_flags;
			this->change_time = time(nullptr);
			return true;
		}

}
