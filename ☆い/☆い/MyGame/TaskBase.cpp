#include "TaskBase.h"

#ifdef _DEBUG
#include "..\StageManager.h"
#endif // _DEBUG

//�X�^�e�B�b�N�ϐ��̏�����
ResourceBase *ResourceBase::top = nullptr;

ResourceBase::ResourceBase()
{
	next = nullptr;
	prev = nullptr;
}

//
void ResourceBase::Remove(const char *resourcename_)
{
	if (top)
	{
		if (resourcename_)
		{
			for (ResourceBase *now = top; now != nullptr;)
			{
				ResourceBase *next = now->next;
				if (now->rname == resourcename_)
				{
					ResourceBase *prev = now->prev;

					if (now == top) top = nullptr;
					delete now;

					if (prev) prev->next = next;
					else top = next;
					now = next;
					if (now) now->prev = prev;
				}
				else now = next;
			}
		}
		else
		{
			ResourceBase *buf = nullptr;
			for (ResourceBase *it = top; it != nullptr; it = buf)
			{
				buf = it->next;
				delete it;
			}
			top = nullptr;
		}
	}
}

//�X�^�e�B�b�N�ϐ��̏�����
TaskBase *TaskBase::top = nullptr;

TaskBase::TaskBase()
{
	this->next = nullptr;
	this->prev = nullptr;
	this->wait = 0;
	this->updflag = true;
	this->tstate = ACTIVE;
}

void TaskBase::SysFinalize()
{
	RB::Remove();
	if (top)
	{
		for (TB_ptr it = top; it != nullptr;)
		{
			TB_ptr next = it->next;
			TB_ptr prev = it->prev;

			it->Finalize();

			delete it;

			if (prev)prev->next = next;
			else top = next;
			it = next;
			if (it)it->prev = prev;
		}
	}
}

bool TaskBase::SysUpdate()
{
	if (top)
	{
		for (TB_ptr it = top; it != nullptr;)
		{
			if (it->next)it->next->prev = it;

			if (it->tstate == ACTIVE)
			{
				if (it->updflag)
				{
					it->Update();
				}
				else if (it->wait > 0)
				{
					--it->wait;
					if (it->wait == 0)
					{
						it->updflag = true;
					}
				}
				it = it->next;
			}
			else if (it->tstate == END)
			{
				TB_ptr next = it->next;
				TB_ptr prev = it->prev;

				it->Finalize();

				delete it;

				if (prev)prev->next = next;
				else top = next;
				it = next;
				if (it)it->prev = prev;
			}
		}
		return 0;
	}
	return 1;
}

void TaskBase::SysRender()
{
	if (top)
	{
		std::multimap<float, TaskBase *> mDrawMap;
		for (TB_ptr it = top; it != nullptr; it = it->next)
		{
			mDrawMap.insert(std::make_pair(it->GetRenderPriority(), it));
		}
		for (auto mIt : mDrawMap)
		{
			if (mIt.second->tstate == ACTIVE) mIt.second->Render();
		}
		//for (TB_ptr it = top; it != nullptr; it = it->next)
		//{
		//	if (it->tstate == ACTIVE)
		//		it->Render();
		//}

#ifdef _DEBUG
		if (auto sm = Find<StageManager::Obj>("�X�e�[�W�����^�X�N"))
		{
			if (sm->bIsDebug) {
				int pos = 0;
				for (TB_ptr it = top; it != nullptr; it = it->next)
				{
					Font f;
					f.FontCreate("���C���I");
					f.Draw(&Point(pos / 50 * 180.f, pos % 50 * 20.f), it->tname.c_str());
					++pos;
				}
			}
		}
#endif //_DEBUG
	}
}

void TaskBase::Remove(TaskBase *endtask_)
{
	if (endtask_) endtask_->tstate = END;
}

void TaskBase::RemoveAll(const char *taskname_, RemoveFlag rflag_)
{
	if (rflag_ == REMOVE_NAME)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (taskname_)
			{
				if (now->tname == taskname_)
					now->tstate = END;
			}
			else now->tstate = END;
		}
	}
	else
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (taskname_)
			{
				if (now->tname != taskname_)
					now->tstate = END;
			}
			else now->tstate = END;
		}
	}
}

void TaskBase::RemoveAll(const std::initializer_list<std::string> &iInitList, RemoveFlag rflag_)
{
	if (rflag_ == REMOVE_NAME)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			bool bEndTaskFlag = false;
			for (const auto &it : iInitList)
			{
				if (now->tname == it)
				{
					bEndTaskFlag = true;
					break;
				}
			}
			if (bEndTaskFlag)
			{
				now->tstate = END;
			}
		}
	}
	else
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			bool bEndTaskFlag = true;
			for (const auto &it : iInitList)
			{
				if (now->tname == it)
				{
					bEndTaskFlag = false;
					break;
				}
			}
			if (bEndTaskFlag)
			{
				now->tstate = END;
			}
		}
	}
}

void TaskBase::SetName(const char *taskname_)
{
	this->tname = taskname_;
}

void TaskBase::Pause(const std::initializer_list<std::string> &iInitList, const u_int waitframe_, PauseFlag pflag_)
{
	if (pflag_ == PauseFlag::PAUSE_NAME)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			bool bFlag = false;
			for (const auto &it : iInitList)
			{
				if (now->tname == it)
				{
					bFlag = true;
					break;
				}
			}
			if (bFlag)
			{
				now->updflag = false;
				now->wait = waitframe_;
			}
		}
	}
	else
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			bool bFlag = true;
			for (const auto &it : iInitList)
			{
				if (now->tname == it)
				{
					bFlag = false;
					break;
				}
			}
			if (bFlag)
			{
				now->updflag = false;
				now->wait = waitframe_;
			}
		}
	}
}
void TaskBase::Pause(const char *taskname_, const u_int waitframe_, PauseFlag pflag_)
{
	if (pflag_ == PauseFlag::PAUSE_NAME)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (now->tname == taskname_)
			{
				now->updflag = false;
				now->wait = waitframe_;
			}
		}
	}
	else
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (now->tname != taskname_)
			{
				now->updflag = false;
				now->wait = waitframe_;
			}
		}
	}
}

void TaskBase::Pause(const u_int waitframe_)
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		now->updflag = false;
		now->wait = waitframe_;
	}
}

void TaskBase::Pause(const char *taskname_, PauseFlag pflag_)
{
	if (pflag_ == PauseFlag::PAUSE_NAME)
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (now->tname == taskname_)
			{
				now->updflag = false;
				now->wait = -1;
			}
		}
	}
	else
	{
		for (TaskBase *now = top; now != nullptr; now = now->next)
		{
			if (now->tname != taskname_)
			{
				now->updflag = false;
				now->wait = -1;
			}
		}
	}
}

void TaskBase::Pause()
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		now->updflag = false;
		now->wait = -1;
	}
}

void TaskBase::Restart(const char *taskname_)
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		if (now->tname == taskname_)
		{
			now->updflag = true;
			now->wait = 0;
		}
	}
}

void TaskBase::Restart()
{
	for (TaskBase *now = top; now != nullptr; now = now->next)
	{
		now->updflag = true;
		now->wait = 0;
	}
}

void TaskBase::SetRenderPriority(const float afPriority)
{
	fpriority = Clamp(afPriority, 0.f, 1.f);
}

const float TaskBase::GetRenderPriority() const
{
	return fpriority;
}