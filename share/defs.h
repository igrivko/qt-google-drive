#ifndef DEF_H
#define DEF_H

#define GET_FULL_ROOT_CONTENT QString("https://docs.google.com/feeds/default/private/full/folder%3Aroot/contents")
#define GET_FILES_IN_FOLDER QString("https://docs.google.com/feeds/default/private/full/")
#define ROOT_TAG QString("https://docs.google.com/feeds/default/private/full/folder%3Aroot")
#define PARENT_TAG QString("http://schemas.google.com/docs/2007#parent")
#define UPLOAD_TAG QString("http://schemas.google.com/g/2005#resumable-create-media")
#define ICON_TAG QString("http://schemas.google.com/docs/2007#icon")
#define DELETE_FILE QString("https://docs.google.com/feeds/default/private/full/file:")
#define CREATE_FOLDER QString("https://www.googleapis.com/drive/v2/files")
#define COPY_FILE QString("https://docs.google.com/feeds/default/private/full/document:")
#define COPY_FILE_FIRST_QUERY_PART QString("https://www.googleapis.com/drive/v2/files/")
#define COPY_FILE_LAST_QUERY_PART QString("/copy")

#define CONTENTS QString("/contents")
#define MAX_RESULTS QString("?max-results=10000")

#define ACCESS_TOKEN QString("access_token")
#define REFRESH_TOKEN QString("refresh_token")
#define TOKEN_EXPIRES_IN QString("expires_in")

#define HIERARCHY_ATTRIBUTE_TAG(param) param("rel")
#define FYLE_TYPE_ATTRIBUTE_TAG(param) param("type")
#define FYLE_TYPE_SRC_ATTRIBUTE_TAG(param) param("src");
#define HIERARCHY_VALUE_TAG(param) param("href")
#define SELF_TAG QString("self")
#define FOLDER_TITLE_TAG QString("title")
#define FILE_TITLE_TAG QString("docs:filename")
#define FILE_SIZE_TAG QString("docs:size")
#define PUBLISHED_FILE_TAG QString("published")
#define UPDATED_FILE_TAG QString("updated")
#define EDITED_FILE_TAG QString("app:edited")
#define AUTHOR_TAG QString("author")
#define ENTRY_TAG QString("entry")

#define FOLDER_TYPE 0
#define FILE_TYPE 1

#define FOLDER_TYPE_STR QString("folder")
#define FILE_TYPE_STR QString("file")
#define CONTENT QString("content")

#define WORK_DIR QString("Working Directory")
#define INIT_LOAD QString("Initial Load")
#define LEFT_PANEL QString("Left")
#define RIGHT_PANEL QString("Right")
#define CURRENT_PANEL QString("Current Panel")
#define PANEL QString("Panel-")
#define CURRENT_FOLDER_URL QString("Current Folder URL")
#define CURRENT_FOLDER_PATH QString("Current Folder Path")
#define PATHES_URLS QString("Pathes URLs")

#define PARENT_FOLDER_SIGN QString("[..]")

#endif // DEF_H
