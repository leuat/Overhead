#include "uniform.h"


void Uniform::SetUniform() {
    if (m_type==tVec3) glUniform3f(m_id,m_vec3.x,m_vec3.y,m_vec3.z);

            if (m_type==tScalar) {
            if (m_arrSize==1)
            glUniform1f(m_id, m_fval);
            else
                glUniform1fv(m_id, m_arrSize, m_arr);

         }
                if (m_type==tMat4) {
            glUniformMatrix4fv(m_id, 1, GL_FALSE, &m_mat4[0][0]);
         //   printf(": %s, %d\n", m_name.c_str(), m_id);
        }
        if (m_type==tMat3) glUniformMatrix3fv(m_id, 1, GL_FALSE, &m_mat3[0][0]);

}
