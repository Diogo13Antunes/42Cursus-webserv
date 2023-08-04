/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateHeaderState.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcandeia <dcandeia@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:43:05 by dsilveri          #+#    #+#             */
/*   Updated: 2023/08/03 12:14:37 by dcandeia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "IStateRes.hpp"

class CreateHeaderState: public IStateRes
{
	private:
		std::string	_getFileName(std::string reqTarget, ConfigsData &conf);
		size_t		_getFileSize(std::string fileName);
		bool		_isFileReadable(std::string fileName);
		void		_createHeader(std::string &header, std::string fileName, Event *event);
		void		_createHeaderDefaultError(std::string &header, int errorCode, Event *event);
		std::string	_getFileType(std::string fileName);
		std::string _getMimeType(std::string fileExt);

	public:
		CreateHeaderState(void);
		CreateHeaderState(const CreateHeaderState &src);
		~CreateHeaderState(void);
		CreateHeaderState &operator=(const CreateHeaderState &src);

		StateResType handle(Event *event, ConfigsData configsData);
};
