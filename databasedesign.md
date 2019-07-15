# Database Design
## Tables
#### File
| Field  | Type                      | Description                 |
| ------ | ------------------------- | --------------------------- |
| FileId | auto incrementing integer | primary key                 |
| TypeId | integer                   | foreign key from type table |
| Name   | varchar(255)              | filename without extension  |
| Path   | varchar(255)              | complete file path          |

#### Type
| Field  | Type                      | Description  |
| ------ | ------------------------- | ------------ |
| TypeId | auto incrementing integer | primary key  |
| Name   | varchar(255) unique       | type of file |

#### Tag
| Field | Type                      | Description                         |
| ----- | ------------------------- | ----------------------------------- |
| TagId | auto incrementing integer | primary key                         |
| Name  | varchar(255)              | name the tag will be displayed with |

#### FileTag
| Field  | Type    | Description                 |
| ------ | ------- | --------------------------- |
| FileId | integer | foreign key from file table |
| TagId  | integer | foreign key from tag table  |
