#pragma once
#include <deque>

class CMainFrame;

extern CMainFrame* main_frame;

class debug_kernel
{
public:
	debug_kernel(void);
	~debug_kernel(void);

public:
	enum debug_status
	{
		STOP,
		RUN,
		BREAK
	};

	struct  breakpoint_t
	{
		DWORD address;	//�ϵ��ַ
		byte org_data;	//�ϵ㴦��ԭʼ����
		bool valid;	//�ϵ�ʵ�����Ƿ�������
		bool user_enable;	//�û��Ƿ������˸öϵ�

		int hits;	// ���д���
		bool is_once; // �Ƿ���һ���Ե�
	};

	// ����һ��exe����ʼ����
	bool load_exe(std::string& exe_path, std::string& command_str,std::string& current_path);
	// ���ӵ�ָ���Ľ��̲���ʼ����
	bool attach_process(DWORD pid);

	// ��������
	bool step_in();
	// ��������
	bool step_over();

	// �������ԣ����б����Խ���
	bool continue_debug(DWORD continue_status = DBG_CONTINUE,bool disable_current_bp = false);

	bool add_breakpoint(DWORD address,bool is_once = false);


	bool read_memory(DWORD address,void* buffer,size_t size,SIZE_T* num_read = NULL );
	bool write_memory(DWORD address,void* data,SIZE_T size, SIZE_T* num_written = NULL);
	bool modify_memory_prop(DWORD address,SIZE_T size,DWORD new_protect,DWORD* old_protect = NULL);
	bool virtual_query_ex(DWORD address,MEMORY_BASIC_INFORMATION& info);
	breakpoint_t* find_breakpoint_by_address(DWORD address);
	// �û����öϵ�
	bool enable_breakpoint(breakpoint_t* bp);
	bool enable_breakpoint(DWORD address);
	// �û����öϵ�
	bool disable_breakpoint(breakpoint_t* bp);
	bool disable_breakpoint(DWORD address);
	// ʹ�ϵ���Ч
	bool valid_breakpoint(breakpoint_t* bp);
	bool valid_breakpoint(DWORD address);
	// ʹ�ϵ���Ч��Ϊ�˽��е����Ȳ���ʱ���ܶϵ��Ӱ�죬�������ǽ��öϵ㣩
	bool invalid_breakpoint(breakpoint_t* bp);
	bool invalid_breakpoint(DWORD address);
	bool delete_breakpoint(DWORD address);
	void update_breakpoint_starus(bool disable_current_bp);

	std::vector<breakpoint_t>& get_bp_list()
	{
		return bp_vec_;
	}

	const CONTEXT& get_current_context()
	{
		return context_;
	}


	bool symbol_from_addr(DWORD addr,std::string& symbol,bool allow_in_func = false);
	bool symbol_from_addr( DWORD addr,PSYMBOL_INFO symbol_info);
	bool stack_walk(STACKFRAME64& stack_frame, CONTEXT& context);
	bool stop_debug();

	bool break_process()
	{
		return DebugBreakProcess(handle_) == true;
	}

	debug_status get_debug_status()
	{
		return debug_status_;
	}

	void add_ui_event(DWORD type,DWORD param1 = 0,DWORD param2 = 0)
	{
		ui_event_t event = {type,param1,param2};
		ui_event_.push_back(event);
	}

	void wait_for_debug_thread_exit()
	{
		WaitForSingleObject(debug_thread_,INFINITE);
	}

private:
	// ���һ��WaitForDebugEvent��ȡ���ĵ����¼�
	DEBUG_EVENT debug_event_;
	// ���һ�ε����¼�ʱ���߳�context
	CONTEXT context_;
	//HANDLE process_handle_;
	bool debugee_exit_;
	//DWORD process_id_;
	debug_status debug_status_;

	std::vector<breakpoint_t> bp_vec_;

	// �����Խ��̵Ľ��̾��
	HANDLE handle_;
	// �����Խ��̵Ľ���ID
	DWORD pid_;

	std::string sym_search_path_;

	struct load_dll_info_t 
	{
		HANDLE file_handle;
		DWORD base_of_dll;
		std::string dll_path;
	};

	std::vector<load_dll_info_t> load_dll_info_;

	struct ui_event_t
	{
		DWORD type;
		DWORD param1;
		DWORD param2;
	};
	std::deque<ui_event_t> ui_event_;

	HANDLE debug_thread_;

private:
	void debug_thread_proc();
	void  on_idle();
	void on_create_process_event(const CREATE_PROCESS_DEBUG_INFO& create_process_info);
	void on_exit_process_event(const EXIT_PROCESS_DEBUG_INFO& exit_process);
	void on_create_thread_event(const CREATE_THREAD_DEBUG_INFO& create_thread);
	void on_exit_thread_event(const EXIT_THREAD_DEBUG_INFO& exit_thread);
	void on_load_dll_event(const LOAD_DLL_DEBUG_INFO& load_dll);
	void on_unload_dll_event(const UNLOAD_DLL_DEBUG_INFO& unload_dll);
	void on_output_debug_string_event(const OUTPUT_DEBUG_STRING_INFO& debug_string);
	void on_rip_event(const RIP_INFO& rip_info);
	void on_exception_event(const EXCEPTION_DEBUG_INFO& debug_exception);

	bool load_symbol(const load_dll_info_t& info);


	std::string exe_path_;
	std::string command_str_;
	std::string current_path_;

	static unsigned __stdcall load_exe_thread_func(void* pArg);
	static unsigned __stdcall attach_process_thread_func(void* pArg);


////////////////////////////////////////////////////////////////////////////////////////////////
	//memory map���
public:
	struct section_info_t
	{
		char	name[IMAGE_SIZEOF_SHORT_NAME+1];
		byte*	start_addr;
		DWORD	size;
	};

	struct module_info_t 
	{
		BYTE  * module_base_addr;        // Base address of module in th32ProcessID's context
		DWORD   module_base_size;        // Size in bytes of module starting at modBaseAddr
		char    module_name[MAX_MODULE_NAME32 + 1];
		DWORD	pe_header_addr;
		int		section_nums;
		section_info_t	section_info[96];

		std::vector<BYTE*> entry_vector;
	};

	struct memory_region_info_t 
	{
		BYTE*	start_addr;
		DWORD	size;
		std::string	owner_name;
		std::string section_name;
		// 		BYTE*	pSectionStart;
// 		DWORD	dwContains;
		DWORD	type;
		DWORD	protect;
		DWORD	alloc_protect;

		std::vector<BYTE*> entry_vector;
		//std::string	strMapAs;
	};

	std::vector<memory_region_info_t>	memory_info_vector_;
	std::vector<module_info_t>	module_vector_;

	void refresh_memory_map(void);
	bool get_memory_info_by_addr(const void* addr,memory_region_info_t& info);
	void set_sym_search_path(const char* paths, bool reload);
};

