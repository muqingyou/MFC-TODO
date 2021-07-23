# ifndef _THING_H_
# define _THING_H_
	class Thing
	{
	
	public:
		CString title;
		CString ddl;
		int span;
		int need;
		Thing(CString title,CString ddl,int span,int need) {
			title = title;
			ddl = ddl;
			span = span;
			need = need;
		};

	};

#endif


