#include <iostream>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/GetObjectRequest.h>
#include <fstream>
bool GetObject(const Aws::String &objectKey,
                           const Aws::String &fromBucket,
                           const Aws::Client::ClientConfiguration &clientConfig) {
    Aws::S3::S3Client client(clientConfig);

    Aws::S3::Model::GetObjectRequest request;
    request.SetBucket(fromBucket);
    request.SetKey(objectKey);

    Aws::S3::Model::GetObjectOutcome outcome =
            client.GetObject(request);

    if (!outcome.IsSuccess()) {
        const Aws::S3::S3Error &err = outcome.GetError();
        std::cerr << "Error: GetObject: " <<
                  err.GetExceptionName() << ": " << err.GetMessage() << std::endl;
    }
    else {
        std::cout << "Successfully retrieved '" << objectKey << "' from '"
                  << fromBucket << "'." << std::endl;
    }

    return outcome.IsSuccess();
}


int main() {
    Aws::SDKOptions options;
    Aws::InitAPI(options);
    {
        //TODO(user): Change bucketName to the name of a bucket in your account.
        const Aws::String bucketName = "bucket";

        //TODO(user): Change objectName to the name of an object in the bucket.
        //See create_bucket.cpp and put_object.cpp to create a bucket and load an object into that bucket.
        const Aws::String objectName = "object";

        Aws::Client::ClientConfiguration clientConfig;
        // Optional: Set to the AWS Region in which the bucket was created (overrides config file).
        // clientConfig.region = "us-east-1";
#ifdef LOADSTACK
        clientConfig.endpointOverride = "http://localhost:4653"
#endif

        GetObject(objectName, bucketName, clientConfig);
    }
    Aws::ShutdownAPI(options);

    return 0;
}

