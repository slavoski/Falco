#ifndef I_RENDER_OBJECT
#define I_RENDER_OBJECT

class IRenderObject
{
public:
	IRenderObject(void);
	virtual ~IRenderObject(void);

	virtual void Initialize();
	virtual void Update(float _deltaTime);
	virtual void RenderObject();
	virtual void DestroyObject();

};

#endif