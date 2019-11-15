/*
 * add by shailendra
 *
 */

#include "ike_nbifom_generic_container.h"

#include <daemon.h>
#include <encoding/payloads/notify_payload.h>

typedef struct private_ike_nbifom_generic_container_t private_ike_nbifom_generic_container_t;

/**
 * Private members of a ike_nbifom_generic_container_t task.
 */
struct private_ike_nbifom_generic_container_t {

	/**
	 * Public methods and task_t interface.
	 */
	ike_nbifom_generic_container_t public;

	/**
	 * Assigned IKE_SA.
	 */
	ike_sa_t *ike_sa;

	/**
	 * PTI payload received?
	 */
	bool pti_received;

	/**
	 * Are we the initiator?
	 */
	bool initiator;

};

METHOD(task_t, build_i, status_t,
	private_ike_nbifom_generic_container_t *this, message_t *message)
{
	//ToDo
	return NEED_MORE;
}

METHOD(task_t, process_i, status_t,
	private_ike_nbifom_generic_container_t *this, message_t *message)
{
	//ToDo
	return DESTROY_ME;
}

METHOD(task_t, process_r, status_t,
	private_ike_nbifom_generic_container_t *this, message_t *message)
{
	enumerator_t *enumerator;
	payload_t *payload;

	if (message->get_exchange_type(message) != INFORMATIONAL) {
		return NEED_MORE;
	}
	enumerator = message->create_payload_enumerator(message);
	while (enumerator->enumerate(enumerator, &payload))
	{
		notify_payload_t *notify;
		notify_type_t type;
		chunk_t data, spi;

		if (payload->get_type(payload) != NOTIFY)
		{
			continue;
		}
		notify = (notify_payload_t*)payload;
		type = notify->get_notify_type(notify);
		switch (type)
		{
			case NBIFOM_GENERIC_CONTAINER:
			{
					if(notify)
					{
						spi = notify->get_spi_data(notify);
						if(spi.len)
						{
							DBG1(DBG_IKE,"invalid NBIFOM_GENERIC_CONTAINER notify payload");
						}
						else
						{
							data = notify->get_notification_data(notify);
							DBG1(DBG_IKE,"NBIFOM_GENERIC_CONTAINER notify payload partially handled");
							// ToDo
						}
					}
					break;
			}
			case PTI:
			{
				u_int32_t msgid;
				if(notify)
				{
					spi = notify->get_spi_data(notify);
					if(spi.len)
					{
						DBG1(DBG_IKE,"invalid PTI notify payload");
					}
					else
					{
						data = notify->get_notification_data(notify);
						if (data.len == 4)
						{
							msgid = *((u_int32_t*)data.ptr);
							this->pti_received = true;
							DBG1(DBG_IKE,"PTI notify payload processed");
						}
						else
						{
							DBG1(DBG_IKE,"invalid PTI notify payload with data len %u", data.len);
						}
					}
				}
				break;
			}
			default:
				break;
		}
	}
	enumerator->destroy(enumerator);

	return NEED_MORE;
}

METHOD(task_t, build_r, status_t,
	private_ike_nbifom_generic_container_t *this, message_t *message)
{

	DBG0(DBG_IKE, "add NBIFOM_GENERIC_CONTAINER payload");
	message->add_notify(message, FALSE, NBIFOM_GENERIC_CONTAINER, chunk_empty);
	// ToDo: need to add data in future as per usage
	
	if (this->pti_received) {
		this->pti_received = false;
	}

	return SUCCESS;
}

METHOD(task_t, get_type, task_type_t,
	private_ike_nbifom_generic_container_t *this)
{
	return TASK_IKE_NBIFOM_GENERIC_CONTAINER;
}

METHOD(task_t, destroy, void,
	private_ike_nbifom_generic_container_t *this)
{
	free(this);
}

/*
 * Described in header.
 */
ike_nbifom_generic_container_t *ike_nbifom_generic_container_create(ike_sa_t *ike_sa, bool initiator)
{
	private_ike_nbifom_generic_container_t *this;

	INIT(this,
		.public = {
			.task = {
				.get_type = _get_type,
				.destroy = _destroy,
			},
		},
		.ike_sa = ike_sa,
		.initiator = initiator,
	);

	if (initiator)
	{
		this->public.task.build = _build_i;
		this->public.task.process = _process_i;
	}
	else
	{
		this->public.task.build = _build_r;
		this->public.task.process = _process_r;
	}

	return &this->public;
}

