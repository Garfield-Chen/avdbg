#pragma once

#include <string>
#include <vector>
#include <windows.h>

class TextView
{
public:
	TextView(void);
	~TextView(void);

	// ����
	static const char* const wnd_class_name;
	// ע�ᴰ����
	static bool reg_class();
	// ���ڹ���
	static LRESULT WINAPI TextViewWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	// �����༭�ؼ�
	bool Create(HWND parent_wnd,int x,int y,int width,int height);

	HWND get_hwnd()
	{
		return edit_wnd_;
	}

	// ��ȡ�и�
	int get_line_height()
	{
		return line_height_;
	}
	// �����и�
	void set_line_height(int line_height)
	{
		line_height_ = line_height;
	}
	// ��������
	HFONT set_font(HFONT font)
	{
		HFONT font_tmp = font_;
		font_ = font;
		return font_tmp;
	}
	// ��ȡ�߿�
	int get_margin_width()
	{
		return margin_widrh_;
	}
	// ���ñ߿�
	void set_margin_width(int margin_width)
	{
		margin_widrh_ = margin_width;
		refresh();
	}

private:
	// ��Ϣ�ַ�����
	LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

	void on_create();
	void on_size(UINT flags, int width, int height);
	void on_paint();
	void on_left_button_down(UINT flags,int x,int y);
	void on_v_scroll(UINT code, UINT pos);
	void on_h_scroll(UINT code, UINT pos);
	void set_scroll_status();
	void set_caret_status();

public:
	// ��������һ��
	void add_line(const std::string& line, bool invalid = false)
	{
		EnterCriticalSection(&critical_sections_);
		line_buffer_.push_back(line);
		LeaveCriticalSection(&critical_sections_);
		
		if (h_scroll_max_pos<line.size())
		{
			h_scroll_max_pos = line.size();
		}

		if (invalid)
		{
			refresh();
		}
	}

	// ��ָ����֮�������һ��
	void insert_line(const std::string& line,int index,bool invalid = false)
	{
		EnterCriticalSection(&critical_sections_);
		line_buffer_.insert(line_buffer_.begin() + index,line);
		LeaveCriticalSection(&critical_sections_);

		if (h_scroll_max_pos<line.size())
		{
			h_scroll_max_pos = line.size();
		}

		if (invalid)
		{
			refresh();
		}
	}

	// ɾ��ָ����
	void eraser_line(int index,bool invalid = false)
	{
		EnterCriticalSection(&critical_sections_);
		line_buffer_.erase(line_buffer_.begin() + index);

		std::string line = line_buffer_.at(index);
		if (h_scroll_max_pos == line.size())
		{
			h_scroll_max_pos = 0;
			for each (line in line_buffer_)
			{
				if (h_scroll_max_pos<line.size())
				{
					h_scroll_max_pos = line.size();
				}
			}
		}
		LeaveCriticalSection(&critical_sections_);

		if (invalid)
		{
			refresh();
		}
	}

	// ˢ�´���
	bool refresh(const RECT* rect_ptr = NULL,BOOL erase_bkg = FALSE)
	{
		set_scroll_status();
		return InvalidateRect(edit_wnd_,rect_ptr,erase_bkg);
	}

private:
// 	// �����ھ��
// 	HWND parent_wnd_;
	// �༭�ؼ��Ĵ��ھ��
	HWND edit_wnd_;
	// ����ÿһ��������Ϣ
	std::vector<std::string> line_buffer_;

	// �и�
	int line_height_;
	// �߿��
	int margin_widrh_;
	// ����ɫ
	COLORREF margin_color_;
	// ����
	HFONT font_;
	// ������
	int font_width_;

	// ˮƽ������λ��
	unsigned long h_scroll_pos_;
	// ��ֱ������λ��
	unsigned long v_scroll_pos_;
	// ˮƽ���������ֵ
	unsigned long h_scroll_max_pos;

	// һ���м���
	int page_lines_;
	// һ���м���
	int page_columns_;

	// ���λ��
	int caret_lines_;
	int caret_columns_;
	bool caret_is_hide_;

	CRITICAL_SECTION critical_sections_;
};

