/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "bagel/baglib/expression_object.h"
#include "bagel/baglib/master_win.h"
#include "bagel/baglib/var.h"
#include "bagel/baglib/storage_dev_win.h"

namespace Bagel {

CBagExpressionObject::CBagExpressionObject() : CBagObject() {
	m_xObjType = EXPRESSOBJ;
	m_xExpression = nullptr;
	SetConditional(false);
	SetVisible(false);
	SetTimeless(true);
}

CBagExpressionObject::~CBagExpressionObject() {
	if (m_xExpression != nullptr) {
		delete m_xExpression;
		m_xExpression = nullptr;
	}
	detach();
}

bool CBagExpressionObject::runObject() {
	if (m_xExpression != nullptr) {
		CBagVar xVar;
		m_xExpression->evaluate(false, xVar);

		if (!IsConditional()) {
			if (getFileName().IsEmpty())
				return false;

			int nIndex = getFileName().Find("~~");
			if (nIndex > 0) { // This is a reference
				CBofString sObject = getFileName().Left(nIndex);
				CBofString sProperty = getFileName().Mid(nIndex + 2);

				SDEVMNGR->SetObjectValue(sObject, sProperty, xVar.GetNumValue());

			} else {
				CBagVar *pVar = VARMNGR->GetVariable(getFileName());
				if (pVar)
					pVar->SetValue(xVar.GetValue());
			}
		}
	}

	return CBagObject::runObject();
}

PARSE_CODES CBagExpressionObject::setInfo(bof_ifstream &istr) {
	bool nObjectUpdated = false;

	while (!istr.eof()) {
		char ch = (char)istr.peek();
		switch (ch) {
		//
		//  AS  - n number of slides in sprite
		//
		case '(': {
			m_xExpression = new CBagExpression();
			if (m_xExpression) {
				m_xExpression->setInfo(istr);
				nObjectUpdated = true;
			} else {
				// there was an error
			}
		} break;
		//
		//  No match return from function
		//
		default: {
			PARSE_CODES rc = CBagObject::setInfo(istr);
			if (rc == PARSING_DONE) {
				return PARSING_DONE;
			}

			if (rc == UPDATED_OBJECT) {
				nObjectUpdated = true;
			} else { // rc==UNKNOWN_TOKEN
				if (nObjectUpdated)
					return UPDATED_OBJECT;

				return UNKNOWN_TOKEN;
			}
		}
		break;
		}
	}
	return PARSING_DONE;
}

} // namespace Bagel
